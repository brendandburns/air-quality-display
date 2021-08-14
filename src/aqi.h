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

typedef enum {
  NONE,
  WOODSMOKE
} Adjustment;

void applyAdjustment(PMS::DATA *data, Adjustment adj);
float calculateAqi(const PMS::DATA *data);
QualityStage measure(const PMS::DATA *data);

#endif