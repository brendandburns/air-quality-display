#ifndef __DISPLAYS_H__
#define __DISPLAYS_H__

#include <TFT_eSPI.h>
#include "aqi.h"

typedef enum {
  PM2_5,
  AQI
} DisplayMode;

uint32_t stateColor(QualityStage state);

void nop(TFT_eSPI* tft, void* data);

void drawInfo(TFT_eSPI *tft, void* data);

void drawState(TFT_eSPI* tft, void* data);
void refreshState(TFT_eSPI* tft, void* data);
void clickState(void* data);

void drawSettings(TFT_eSPI* tft, void* data);
void clickSettings(void* data);

const Adjustment adjustment();

#endif // __DISPLAYS_H__