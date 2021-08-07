#include "screens.h"

Screens::Screens(screen_t screens[], size_t count) : screens(screens), count(count), current(0) {}

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
    if (this->screens[this->current].render != NULL) {
        this->screens[this->current].render();
    }
}

void Screens::refresh() {
    if (this->screens[this->current].render != NULL) {
        this->screens[this->current].refresh();
    }
}

int Screens::currentScreen() {
    return this->current;
}