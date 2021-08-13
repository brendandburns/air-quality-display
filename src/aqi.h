#ifndef __AQI_H__
#define __AQI_H__

#include <PMS.h>

typedef enum {
  GOOD,
  MODERATE,
  USG,
  UNHEALTHY,
  VERY_UNHEALTHY,
  HAZARDOUS
} QualityStage;

float calculateAqi(const PMS::DATA *data);
QualityStage measure(const PMS::DATA *data);

#endif