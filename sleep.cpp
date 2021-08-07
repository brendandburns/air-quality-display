#include "sleep.h"

bool sleeping;
long woke;

// Taken from: https://github.com/Bodmer/TFT_eSPI/issues/715
void displaySleep(TFT_eSPI* spi, bool sleep)
{
    if (sleep)
    {
        spi->writecommand(0x10);   // Send command to put the display to sleep.
        delay(150);                // Delay for shutdown time before another command can be sent.
    }
    else
    {
        spi->init();               // This sends the wake up command and initialises the display
	    delay(50);            // Extra delay to stop a "white flash" while the TFT is initialising.
    }
}

void initDisplaySleep(TFT_eSPI* spi) {
    sleeping = false;
    woke = millis();
    displaySleep(spi, false);
}

void maybeDisplaySleep(TFT_eSPI* spi, long timeout) {
    if (sleeping) {
        return;
    }
    if ((millis() - woke) > timeout) {
        displaySleep(spi, true);
        sleeping = true;
    }
}

bool wakeDisplay(TFT_eSPI* spi) {
    if (!sleeping) {
        return false;
    }
    displaySleep(spi, false);
    woke = millis();
    sleeping = false;
    return true;
}