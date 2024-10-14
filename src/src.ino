#include <WiFi.h>
#include <ESPAsyncWebServer.h>

#include <PMS.h>

#define SMOOTH_FONT
#include <TFT_eSPI.h>
#include <SPI.h>
#include <Wire.h>
#include <Button2.h>

#include "aqi.h"
#include "battery.h"
#include "colors.h"
#include "content.h"
#include "data.h"
#include "displays.h"
#include "hotspot.h"
#include "plot.h"
#include "screens.h"
#include "sleep.h"

#include "icons/air.h"
#include "icons/graph.h"
#include "icons/settings.h"
#include "icons/wifi.h"

AsyncWebServer server(80);
PMS pms(Serial1);
PMS::DATA data;

TFT_eSPI display(135, 240);
Sleep displaySleep(&display);

#define BUTTON_1            35
#define BUTTON_2            0

Button2 btn1(BUTTON_1);
Button2 btn2(BUTTON_2);

DataSet dataset(48);
Hotspot hotspot;
QualityStage last_state = GOOD;
AirQualityColors colors(&(data.PM_AE_UG_2_5));

void startStopWifi(void* data) {
  if (hotspot.enabled()) {
    hotspot.shutdown();
    server.end();
  } else {
    hotspot.setup();

    server.on("/", handleIndex);
    server.on("/index.html", handleIndex);
    server.on("/api", handleApi);
    server.onNotFound(handleNotFound);
    server.begin();
  }
}

void refreshGraph(Screens* screens, void* ptr) {
  const float *datum = dataset.data();
  screens->tft()->fillScreen(TFT_BLACK);
  Graph::boxPlot(screens->tft(), datum, dataset.count(), 10, 10, 150, 5, 135, AirQualityColors::stateColors(measure(data.PM_AE_UG_2_5)));
}

Screens screen(new screen_t[4] {
  { name: "state", render: drawState, refresh: refreshState, click: clickState, icon: air, data: &data},
  { name: "info", render: drawInfo, refresh: nop, click: startStopWifi, icon: wifi, data: &hotspot},
  { name: "graph", render: nop, refresh: refreshGraph, click: NULL, icon: graphIcon},
  { name: "settings", render: drawSettings, refresh: refreshSettings, click: clickSettings, icon: settings, data: &data},
}, 4, &display, &colors, &displaySleep);

void setup() {
  Serial.begin(115200);
  Serial1.begin(9600, SERIAL_8N1, 26, 25);

  setSensorData(&dataset);

  display.init();
  display.setRotation(1);

  screen.render();
  screen.refresh();

  displaySleep.init();
  btn1.setPressedHandler([](Button2 & b) {
    if (displaySleep.wake()) {
      screen.render();
      screen.refresh();
      return;
    }
    screen.next();
  });

  btn2.setPressedHandler([](Button2 & b) {
    if (displaySleep.wake()) {
      screen.render();
      screen.refresh();
      return;
    }
    screen.click();
  });

  Battery::battery()->init();
}

void button_loop()
{
    btn1.loop();
    btn2.loop();
}

#define POLL_PERIOD 1000
#define SLEEP_TIMEOUT 30000
long last_read = 0;
void loop() {
  button_loop();
  Battery::battery()->loop();

  if ((millis() - last_read) < POLL_PERIOD) {
    delay(50);
    return;
  }
  if (pms.read(data))
  {
    data.PM_AE_UG_2_5 = applyAdjustment(data.PM_AE_UG_2_5, adjustment());
    last_read = millis();
    dataset.addDataPoint(data.PM_AE_UG_2_5);
    if (dataset.data()[0] != dataset.data()[1]) {
      QualityStage state = measure(data.PM_AE_UG_2_5);
      if (state != last_state) {
        screen.render();
        last_state = state;
      }
      screen.refresh();
    }
  }
  displaySleep.loop(SLEEP_TIMEOUT);
}