#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <PMS.h>

#define SMOOTH_FONT
#include <TFT_eSPI.h>
#include <SPI.h>
#include <Wire.h>
#include <Button2.h>

#include "content.h"
#include "plot.h"
#include "screens.h"
#include "data.h"
#include "sleep.h"
#include "battery.h"

AsyncWebServer server(80);
PMS pms(Serial1);
PMS::DATA data;

TFT_eSPI tft = TFT_eSPI(135, 240);
Sleep displaySleep = Sleep(&tft);

#define BUTTON_1            35
#define BUTTON_2            0

Button2 btn1(BUTTON_1);
Button2 btn2(BUTTON_2);

Graph graph(&tft);
DataSet dataset(48);
Battery battery;

String *ap_ssid = NULL;
String *ap_pass = new String("airquality");

typedef enum {
  GOOD,
  MODERATE,
  USG,
  UNHEALTHY,
  HAZARDOUS
} QualityStage;

QualityStage last_state = GOOD;

void drawInfo() {
  tft.fillScreen(TFT_BLACK);

  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  tft.setTextFont(4);
  tft.drawString((String("WiFi: ") + *ap_ssid).c_str(), 10, 10);
  tft.drawString((String("Password: ") + *ap_pass).c_str(), 10, 40);
  tft.drawString((String("http://") + WiFi.softAPIP().toString() + "/").c_str(), 10, 70);
}

void refreshGraph() {
  const float *data = dataset.data();
  tft.fillScreen(TFT_BLACK);
  graph.boxPlot(data, dataset.count(), 10, 10, 150, 5, 135, stateColor(measure()));
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
  tft.fillScreen(stateColor(measure()));
}

void refreshState() {
  u32_t color = stateColor(measure());
  switch (color) {
    case TFT_PURPLE:
      tft.setTextColor(TFT_WHITE, color);
    default:
      tft.setTextColor(TFT_BLACK, color);
  }
  tft.setTextFont(4);
  tft.drawString((String("PM2.5: ") + data.PM_AE_UG_2_5 + "     ").c_str(), 50, 50);
  if (battery.charging()) {
    tft.drawString("Chrg", 5, 110);
  } else {
    tft.drawString((String("  ") + battery.percentage() + "%").c_str(), 5, 110);
  }
}

void nop() {}

Screens screen(new screen_t[3] {
  { name: "state", render: drawState, refresh: refreshState},
  { name: "info", render: drawInfo, refresh: nop},
  { name: "graph", render: nop, refresh: refreshGraph},
}, 3, &displaySleep);

void setup() {
  Serial.begin(115200);
  Serial1.begin(9600, SERIAL_8N1, 26, 25);

  String mac = WiFi.macAddress();
  ap_ssid = new String("AirQuality-" + mac.substring(0, 2) + mac[3]);

  WiFi.softAP(ap_ssid->c_str(), ap_pass->c_str());
  Serial.println("Access point running.");
  Serial.print("SSID: "); Serial.println(ap_ssid->c_str());
  Serial.print("Password: "); Serial.println(ap_pass->c_str());
  Serial.print("IP address: ");
  Serial.print(WiFi.softAPIP());
  Serial.println("");
  Serial.print("Please connect to http://"); Serial.println(WiFi.softAPIP());

  server.on("/", handleIndex);
  server.on("/index.html", handleIndex);
  server.on("/api", handleApi);
  server.onNotFound(handleNotFound);
  server.begin();

  setSensorData(&dataset);

  tft.init();
  tft.setRotation(1);

  screen.render();
  screen.refresh();

  displaySleep.init();
  btn1.setPressedHandler([](Button2 & b) {
    if (displaySleep.wake()) {
      return;
    }
    screen.next();
  });

  btn2.setPressedHandler([](Button2 & b) {
    if (displaySleep.wake()) {
      return;
    }
    screen.previous();
  });

  battery.init();
}

void button_loop()
{
    btn1.loop();
    btn2.loop();
}

QualityStage measure() {
  if (data.PM_AE_UG_2_5 < 13) {
    return GOOD;
  }
  if (data.PM_AE_UG_2_5 < 35) {
    return MODERATE;
  }
  if (data.PM_AE_UG_2_5 < 55) {
    return USG;
  }
  if (data.PM_AE_UG_2_5 < 150) {
    return UNHEALTHY;
  }
  return HAZARDOUS;
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
      QualityStage state = measure();
      if (state != last_state) {
        screen.render();
        last_state = state;
      }
      screen.refresh();
    }
  }
  displaySleep.loop(SLEEP_TIMEOUT);
}