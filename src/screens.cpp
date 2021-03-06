#include "screens.h"

Screens::Screens(screen_t screens[], size_t count, TFT_eSPI* tft, Colors* colors, Sleep *sleep)
    : screens(screens), count(count), current(0), _tft(tft), _colors(colors), sleep(sleep) {}

void Screens::next() {
    this->current = (this->current + 1) % this->count;
    this->render();
    this->refresh();
}

void Screens::previous() {
    if (this->current == 0) {
        this->current = this->count - 1;
    } else {
        this->current--;
    }
    this->render();
    this->refresh();
}

void Screens::render() {
    if (this->sleep != NULL && !(this->sleep->isAwake())) return;

    const screen_t *screen = &(this->screens[this->current]);
    if (screen->render != NULL) {
        screen->render(this, screen->data);
    }
    if (screen->icon != NULL) {
        this->_tft->drawXBitmap(10, 10, screen->icon, 24, 24, _colors->foreground());
    }
}

void Screens::refresh() {
    if (this->sleep != NULL && !(this->sleep->isAwake())) return;

    const screen_t *screen = &(this->screens[this->current]);
    if (screen->refresh != NULL) {
        screen->refresh(this, screen->data);
    }
}

void Screens::click() {
    if (this->sleep != NULL && !(this->sleep->isAwake())) return;

    const screen_t *screen = &(this->screens[this->current]);
    if (screen->click != NULL) {
        screen->click(screen->data);
        this->refresh();
    }
}

int Screens::currentScreen() {
    return this->current;
}

TFT_eSPI* Screens::tft() { return _tft; }
Colors* Screens::colors() { return _colors; }