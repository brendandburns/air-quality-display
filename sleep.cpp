#include "sleep.h"

#define TFT_BACKLIGHT_OFF 0

Sleep::Sleep(TFT_eSPI* spi) : spi(spi) {}

// Adapted from: https://github.com/Bodmer/TFT_eSPI/issues/715
void Sleep::displaySleep(bool sleep)
{
    if (sleep)
    {
        this->spi->writecommand(0x10);            // Send command to put the display to sleep.
        digitalWrite(TFT_BL, TFT_BACKLIGHT_OFF);  // Turn off the backlight
        delay(150);                               // Delay for shutdown time before another command can be sent.
    } else {
        this->spi->init();    // This sends the wake up command and initialises the display
        delay(50);            // Extra delay to stop a "white flash" while the TFT is initialising.
    }
}

void Sleep::init() {
    this->sleeping = false;
    this->woke = millis();
    this->displaySleep(false);
}

void Sleep::loop(long timeout) {
    if (this->sleeping) {
        return;
    }
    if ((millis() - woke) > timeout) {
        this->displaySleep(true);
        this->sleeping = true;
    }
}

bool Sleep::wake() {
    if (this->isAwake()) {
        return false;
    }
    this->displaySleep(false);
    this->woke = millis();
    this->sleeping = false;
    return true;
}

bool Sleep::isAwake() {
    return !this->sleeping;
}