#include "mock_arduino.h"

static float analogValue;
static int pinRead;
static int modePin;
static int modeValue;

// Functions for test setup
void setAnalogValue(float value) { analogValue = value; }

float analogRead(int pin) { return analogValue; }
void pinMode(int pin, int mode) {
    modePin = pin;
    modeValue = mode;
}