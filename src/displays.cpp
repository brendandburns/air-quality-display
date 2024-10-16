#include "displays.h"

#include <PMS.h>
#include <WiFi.h>
#include "battery.h"
#include "hotspot.h"
#include "icons/battery.h"

DisplayMode displayMode = PM2_5;

Adjustment adj = WOODSMOKE;

const Adjustment adjustment() {
    return adj;
}

void setError() {
  displayMode = ERROR;
}

void clearError() {
  displayMode = PM2_5;
}

void nop(Screens* screens, void* data) {}

void drawInfo(Screens *screens, void* data) {
  Hotspot* hotspot = (Hotspot*) data;
  TFT_eSPI* tft = screens->tft();
  tft->fillScreen(screens->colors()->background());
  tft->setTextColor(screens->colors()->foreground(), screens->colors()->background());
  tft->setTextFont(4);
  if (hotspot->enabled()) {
    tft->drawString((String("WiFi: ") + hotspot->ssid()).c_str(), 10, 40);
    tft->drawString((String("Password: ") + hotspot->password()).c_str(), 10, 70);
    tft->drawString((String("http://") + WiFi.softAPIP().toString() + "/").c_str(), 10, 100);
  } else {
    tft->drawString("WiFi disabled", 10, 40);
  }
}

void drawState(Screens* screens, void* data) {
  screens->tft()->fillScreen(screens->colors()->background());
}

void refreshState(Screens* screens, void* data) {
  TFT_eSPI* tft = screens->tft();
  tft->setTextColor(screens->colors()->foreground(), screens->colors()->background());
  tft->setTextFont(4);
  switch (displayMode) {
    case ERROR:
      tft->drawString(String("Error reading sensor"), 50, 50);
      break;
    case AQI:
      tft->drawString(String("AQI: ") + calculateAqi(((const PMS::DATA*)data)->PM_AE_UG_2_5), 50, 50);
      break;
    default:
      tft->drawString((String("PM2.5: ") + ((const PMS::DATA*) data)->PM_AE_UG_2_5 + "     ").c_str(), 50, 50);
  }
  tft->drawXBitmap(200, 10, batteryIcon, 24, 24, screens->colors()->foreground());
  int width;
  float percentage = Battery::battery()->percentage();
  if (percentage < 0.1) {
    width = 0;
  } else if (percentage < 0.4) {
    width = 5;
  } else if (percentage < 0.8) {
    width = 10;
  } else {
    width = 18;
  }
  tft->fillRect(200, 16, width, 10, screens->colors()->foreground());
}

void clickState(void* ptr) {
  if (displayMode == PM2_5) {
    displayMode = AQI;
  } else {
    displayMode = PM2_5;
  }
}

void drawSettings(Screens* screens, void* data)
{
  screens->tft()->fillScreen(screens->colors()->background());
  refreshSettings(screens, data);
}

void refreshSettings(Screens* screens, void* data)
{
  uint32_t color = screens->colors()->background();
  TFT_eSPI* tft = screens->tft();
  tft->fillRect(50, 50, 200, 100, color);
  tft->setTextColor(screens->colors()->foreground(), color);
  tft->setTextFont(4);
  switch (adj) {
    case WOODSMOKE:
      tft->drawString("Woodsmoke", 50, 50);
      tft->drawString("adjustment", 50, 75);
      break;
    case NONE:
    default:
      tft->drawString("No adjustment", 50, 50);
      break;
  }
}

void clickSettings(void *ptr)
{
  if (adj == WOODSMOKE) {
    adj = NONE;
  }
  else {
    adj = WOODSMOKE;
  }
}
