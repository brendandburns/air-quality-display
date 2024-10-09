#ifndef __AQI_H__
#define __AQI_H__

#include <stdint.h>

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

uint16_t applyAdjustment(const uint16_t pm2_5, Adjustment adj);
float calculateAqi(const uint16_t pm2_5);
QualityStage measure(const uint16_t pm2_5);

#endif