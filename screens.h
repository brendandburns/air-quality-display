#ifndef __SCREENS_H__
#define __SCREENS_H__

#include <stdlib.h>

typedef struct screen_t {
    const char* name;
    void(*render)();
    void(*refresh)();
} screen_t;

class Screens {
    private:
        screen_t *screens;
        size_t count;
        size_t current;
    
    public:
        Screens(screen_t screens[], size_t count);

        void next();
        void previous();
        void render();
        void refresh();
        int currentScreen();
};

#endif // __SCREENS_H__