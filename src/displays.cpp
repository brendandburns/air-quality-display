#include "displays.h"

#include <PMS.h>
#include <WiFi.h>
#include "battery.h"
#include "hotspot.h"

DisplayMode displayMode = PM2_5;

Adjustment adj = WOODSMOKE;

const Adjustment adjustment() {
    return adj;
}

uint32_t stateColor(QualityStage state) {
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

void nop(TFT_eSPI* tft, void* data) {}

void drawInfo(TFT_eSPI *tft, void* data) {
  Hotspot* hotspot = (Hotspot*) data;
  tft->fillScreen(TFT_BLACK);
  tft->setTextColor(TFT_GREEN, TFT_BLACK);
  tft->setTextFont(4);
  if (hotspot->enabled()) {
    tft->drawString((String("WiFi: ") + hotspot->ssid()).c_str(), 10, 10);
    tft->drawString((String("Password: ") + hotspot->password()).c_str(), 10, 40);
    tft->drawString((String("http://") + WiFi.softAPIP().toString() + "/").c_str(), 10, 70);
  } else {
    tft->drawString("WiFi disabled", 10, 10);
  }
}

void drawState(TFT_eSPI* tft, void* data) {
  tft->fillScreen(stateColor(measure((const PMS::DATA*) data)));
}

void refreshState(TFT_eSPI* tft, void* data) {
  uint32_t color = stateColor(measure((const PMS::DATA*) data));
  switch (color) {
    case TFT_PURPLE:
      tft->setTextColor(TFT_WHITE, color);
    default:
      tft->setTextColor(TFT_BLACK, color);
  }
  tft->setTextFont(4);
  switch (displayMode) {
    case AQI:
      tft->drawString(String("AQI: ") + calculateAqi((const PMS::DATA*) data), 50, 50);
      break;
    default:
      tft->drawString((String("PM2.5: ") + ((const PMS::DATA*) data)->PM_AE_UG_2_5 + "     ").c_str(), 50, 50);
  }
  if (Battery::battery()->charging()) {
    tft->drawString("Chrg", 5, 110);
  } else {
    tft->drawString((String("  ") + Battery::battery()->percentage() + "%").c_str(), 5, 110);
  }
}

void clickState(void* ptr) {
  if (displayMode == PM2_5) {
    displayMode = AQI;
  } else {
    displayMode = PM2_5;
  }
}

void nop(TFT_eSPI* tft) {}

void drawSettings(TFT_eSPI* tft, void* data)
{
  tft->fillScreen(stateColor(measure((const PMS::DATA*) data)));
  uint32_t color = stateColor(measure((const PMS::DATA*) data));
  switch (color) {
    case TFT_PURPLE:
      tft->setTextColor(TFT_WHITE, color);
    default:
      tft->setTextColor(TFT_BLACK, color);
  }
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
