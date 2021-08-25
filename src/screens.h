#ifndef __SCREENS_H__
#define __SCREENS_H__

#include <stdlib.h>
#include <TFT_eSPI.h>

#include "sleep.h"

typedef struct screen_t {
    const char* name;
    void(*render)(TFT_eSPI* tft, void* data);
    void(*refresh)(TFT_eSPI* tft, void* data);
    void(*click)(void* data);
    const uint8_t *icon;
    void *data;
} screen_t;

class Screens {
    private:
        screen_t *screens;
        size_t count;
        size_t current;
        Sleep *sleep;
        TFT_eSPI* tft;
    
    public:
        Screens(screen_t screens[], size_t count, TFT_eSPI *tft, Sleep* sleep=NULL);

        void next();
        void previous();
        void render();
        void refresh();
        void click();
        int currentScreen();
};

#endif // __SCREENS_H__