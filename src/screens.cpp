#include "screens.h"

Screens::Screens(screen_t screens[], size_t count, TFT_eSPI* tft, Sleep *sleep)
    : screens(screens), count(count), current(0), tft(tft), sleep(sleep) {}

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
        screen->render(this->tft, screen->data);
    }
    if (screen->icon != NULL) {
        this->tft->drawXBitmap(10, 10, screen->icon, 24, 24, TFT_WHITE);
    }
}

void Screens::refresh() {
    if (this->sleep != NULL && !(this->sleep->isAwake())) return;

    const screen_t *screen = &(this->screens[this->current]);
    if (screen->refresh != NULL) {
        screen->refresh(this->tft, screen->data);
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