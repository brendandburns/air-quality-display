#include "colors.h"

#include "aqi.h"

#ifdef ESP32
#include <TFT_eSPI.h>
#else
#include "mock/mock_arduino.h"
#endif

uint32_t AirQualityColors::stateColors(QualityStage state) {
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

AirQualityColors::AirQualityColors(const uint16_t *pm2_5) : pm2_5(pm2_5) {}

uint32_t AirQualityColors::foreground()
{
    QualityStage stage = measure(*pm2_5);
    if (stage == HAZARDOUS) {
        return TFT_WHITE;
    }
    return TFT_BLACK;
}

uint32_t AirQualityColors::background()
{
    return AirQualityColors::stateColors(measure(*pm2_5));
}