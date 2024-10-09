#include "colors.h"

#include "aqi.h"
#include "displays.h"

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
    return stateColor(measure(*pm2_5));
}