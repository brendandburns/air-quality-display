#ifndef __SLEEP_H__
#define __SLEEP_H__

#include <TFT_eSPI.h>

class Sleep {
    private:
        TFT_eSPI* spi;
        bool sleeping;
        long woke;

        void displaySleep(bool sleep);

    public:
        Sleep(TFT_eSPI* spi);

        void init();
        void loop(long timeout);
        bool wake();
        bool isAwake();
};

#endif