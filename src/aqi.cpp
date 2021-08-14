#include "aqi.h"

void applyAdjustment(PMS::DATA *data, Adjustment adj)
{
  switch (adj) {
    case WOODSMOKE:
      data->PM_AE_UG_2_5 = 0.55 * data->PM_AE_UG_2_5 + 0.53;
      break;
    case NONE:
    default:
      break;
  }
}

float calculateAqi(const PMS::DATA *data) {
    QualityStage stage = measure(data);
    float aqi_range;
    float pm25_range;
    float low;
    float low_pm25;


    switch (stage) {
        case GOOD:
            aqi_range = 50;
            pm25_range = 12;
            low = 0;
            low_pm25 = 0;
            break;
        case MODERATE:
            aqi_range = 49;
            pm25_range = 33.3;
            low = 51;
            low_pm25 = 12.1;
            break;
        case USG:
            aqi_range = 49;
            pm25_range = 19.9;
            low = 101;
            low_pm25 = 35.5;
            break;
        case UNHEALTHY:
            aqi_range = 49;
            pm25_range = 94.9;
            low = 151;
            low_pm25 = 55.5;
        case VERY_UNHEALTHY:
            aqi_range = 99;
            pm25_range = 99.9;
            low = 201;
            low_pm25 = 150.5;
        case HAZARDOUS:
        default:
            aqi_range = 99;
            pm25_range = 99.9;
            low = 301;
            low_pm25 = 250.5;
    }

    return low + (aqi_range * (data->PM_AE_UG_2_5 - low_pm25)) / pm25_range;
}

QualityStage measure(const PMS::DATA *data) {
  if (data->PM_AE_UG_2_5 < 13) {
    return GOOD;
  }
  if (data->PM_AE_UG_2_5 < 35) {
    return MODERATE;
  }
  if (data->PM_AE_UG_2_5 < 55) {
    return USG;
  }
  if (data->PM_AE_UG_2_5 < 150) {
    return UNHEALTHY;
  }
  if (data->PM_AE_UG_2_5 < 250) {
      return VERY_UNHEALTHY;
  }
  return HAZARDOUS;
}