#ifndef __SCREENS_H__
#define __SCREENS_H__

#include <stdlib.h>
#include "sleep.h"

typedef struct screen_t {
    const char* name;
    void(*render)();
    void(*refresh)();
    void(*click)();
} screen_t;

class Screens {
    private:
        screen_t *screens;
        size_t count;
        size_t current;
        Sleep *sleep;
    
    public:
        Screens(screen_t screens[], size_t count, Sleep* sleep=NULL);

        void next();
        void previous();
        void render();
        void refresh();
        void click();
        int currentScreen();
};

#endif // __SCREENS_H__