#ifndef __DISPLAYS_H__
#define __DISPLAYS_H__

#include "aqi.h"
#include "screens.h"

typedef enum {
  PM2_5,
  AQI,
  ERROR
} DisplayMode;

void clearError();
void setError();

void nop(Screens* tft, void* data);

void drawInfo(Screens *tft, void* data);

void drawState(Screens* tft, void* data);
void refreshState(Screens* tft, void* data);
void clickState(void* data);

void drawSettings(Screens* tft, void* data);
void refreshSettings(Screens* tft, void* data);
void clickSettings(void* data);

const Adjustment adjustment();

#endif // __DISPLAYS_H__