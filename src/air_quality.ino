#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <PMS.h>

#define SMOOTH_FONT
#include <TFT_eSPI.h>
#include <SPI.h>
#include <Wire.h>
#include <Button2.h>

#include "aqi.h"
#include "content.h"
#include "plot.h"
#include "screens.h"
#include "data.h"
#include "sleep.h"
#include "battery.h"
#include "hotspot.h"

AsyncWebServer server(80);
PMS pms(Serial1);
PMS::DATA data;

TFT_eSPI tft(135, 240);
Sleep displaySleep(&tft);

#define BUTTON_1            35
#define BUTTON_2            0

Button2 btn1(BUTTON_1);
Button2 btn2(BUTTON_2);

Graph graph(&tft);
DataSet dataset(48);
Battery battery;
Hotspot hotspot;
QualityStage last_state = GOOD;

typedef enum {
  PM2_5,
  AQI
} DisplayMode;

DisplayMode display = PM2_5;

void startStopWifi() {
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

void drawInfo() {
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  tft.setTextFont(4);
  if (hotspot.enabled()) {
    tft.drawString((String("WiFi: ") + hotspot.ssid()).c_str(), 10, 10);
    tft.drawString((String("Password: ") + hotspot.password()).c_str(), 10, 40);
    tft.drawString((String("http://") + WiFi.softAPIP().toString() + "/").c_str(), 10, 70);
  } else {
    tft.drawString("WiFi disabled", 10, 10);
  }
}

void refreshGraph() {
  const float *datum = dataset.data();
  tft.fillScreen(TFT_BLACK);
  graph.boxPlot(datum, dataset.count(), 10, 10, 150, 5, 135, stateColor(measure(&data)));
}

u32_t stateColor(QualityStage state) {
  switch (state) {
    case GOOD:
      return TFT_GREEN;
    case MODERATE:
      return TFT_YELLOW;
    case USG:
      return TFT_ORANGE;
    case UNHEALTHY:
      return TFT_RED;
    default:
      return TFT_PURPLE;
  }
}

void drawState() {
  tft.fillScreen(stateColor(measure(&data)));
}

void refreshState() {
  u32_t color = stateColor(measure(&data));
  switch (color) {
    case TFT_PURPLE:
      tft.setTextColor(TFT_WHITE, color);
    default:
      tft.setTextColor(TFT_BLACK, color);
  }
  tft.setTextFont(4);
  switch (display) {
    case AQI:
      tft.drawString(String("AQI: ") + calculateAqi(&data), 50, 50);
      break;
    default:
      tft.drawString((String("PM2.5: ") + data.PM_AE_UG_2_5 + "     ").c_str(), 50, 50);
  }
  if (battery.charging()) {
    tft.drawString("Chrg", 5, 110);
  } else {
    tft.drawString((String("  ") + battery.percentage() + "%").c_str(), 5, 110);
  }
}

void clickState() {
  if (display == PM2_5) {
    display = AQI;
  } else {
    display = PM2_5;
  }
}

void nop() {}

Screens screen(new screen_t[3] {
  { name: "state", render: drawState, refresh: refreshState, click: clickState},
  { name: "info", render: drawInfo, refresh: nop, click: startStopWifi},
  { name: "graph", render: nop, refresh: refreshGraph, click: NULL},
}, 3, &displaySleep);

void setup() {
  Serial.begin(115200);
  Serial1.begin(9600, SERIAL_8N1, 26, 25);

  setSensorData(&dataset);

  tft.init();
  tft.setRotation(1);

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

  battery.init();
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
  if (battery.volts() < 3) {
  }
  button_loop();
  if ((millis() - last_read) < POLL_PERIOD) {
    delay(50);
    return;
  }
  if (pms.read(data))
  {
    last_read = millis();
    dataset.addDataPoint(data.PM_AE_UG_2_5);
    if (dataset.data()[0] != dataset.data()[1]) {
      QualityStage state = measure(&data);
      if (state != last_state) {
        screen.render();
        last_state = state;
      }
      screen.refresh();
    }
  }
  displaySleep.loop(SLEEP_TIMEOUT);
}