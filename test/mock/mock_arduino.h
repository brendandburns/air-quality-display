#ifndef __MOCK_ARDUINO_H__
#define __MOCK_ARDUINO_H__

// Functions for test setup
void setAnalogValue(float value);

// Mock functions
#define INPUT 10

float analogRead(int pin);
void pinMode(int pin, int mode);

#endif // __MOCK_ARDUINO_H__