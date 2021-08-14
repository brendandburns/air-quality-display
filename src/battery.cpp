#include "battery.h"

#include <Arduino.h>

#define V_BATTERY_PIN 34

Battery::Battery() : ix(0), readings({0,0,0,0,0,0,0,0,0,0}) {}

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
    float avg;
    for (int i = 0; i < 10; i++) {
        avg += this->readings[i];
    }
    avg = avg / 10;
    return ((int) (10 * (avg - 3) / 1.2)) * 10;
}

void Battery::loop() {
    ix = (ix + 1) % 10;
    readings[ix] = this->volts();
}