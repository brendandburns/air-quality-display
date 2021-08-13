#include "battery.h"

#include <Arduino.h>

#define V_BATTERY_PIN 34

Battery::Battery() {}

void Battery::init() {
    pinMode(V_BATTERY_PIN, INPUT);
}

bool Battery::charging() {
    return this->volts() > 4.3;
}

float Battery::volts() {
    return (float)(analogRead(V_BATTERY_PIN)) / 4095 * 2 * 3.3 * 1.1;
}

int Battery::percentage() {
    return (int) 100 * (this->volts() - 3) / 1.2;
}