#ifndef __SCREENS_H__
#define __SCREENS_H__

#include <stdlib.h>
#include <TFT_eSPI.h>

#include "sleep.h"

typedef struct screen_t;

class Colors {
    public:
        virtual uint32_t foreground() = 0;
        virtual uint32_t background() = 0;
};

class Screens {
    private:
        screen_t *screens;
        size_t count;
        size_t current;
        Sleep *sleep;
        TFT_eSPI* _tft;
        Colors* _colors;
    
    public:
        Screens(screen_t screens[], size_t count, TFT_eSPI *tft, Colors* colors, Sleep* sleep=NULL);

        void next();
        void previous();
        void render();
        void refresh();
        void click();
        int currentScreen();

        TFT_eSPI* tft();
        Colors* colors();
};

typedef struct screen_t {
    const char* name;
    void(*render)(Screens* screens, void* data);
    void(*refresh)(Screens* screens, void* data);
    void(*click)(void* data);
    const uint8_t *icon;
    void *data;
} screen_t;

#endif // __SCREENS_H__