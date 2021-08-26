#include "colors.h"

#include "aqi.h"
#include "displays.h"

AirQualityColors::AirQualityColors(PMS::DATA* data) : data(data) {}

uint32_t AirQualityColors::foreground()
{
    QualityStage stage = measure(data);
    if (stage == HAZARDOUS) {
        return TFT_WHITE;
    }
    return TFT_BLACK;
}

uint32_t AirQualityColors::background()
{
    return stateColor(measure(data));
}