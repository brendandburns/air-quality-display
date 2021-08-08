#ifndef __SLEEP_H__
#define __SLEEP_H__

#include <TFT_eSPI.h>

// Taken from: https://github.com/Bodmer/TFT_eSPI/issues/715
void displaySleep(TFT_eSPI* spi, bool sleep);
void initDisplaySleep(TFT_eSPI* spi);
void maybeDisplaySleep(TFT_eSPI* spi, long timeout);
bool wakeDisplay(TFT_eSPI* spi);
bool displayAwake();

#endif