#ifndef __MOCK_ARDUINO_H__
#define __MOCK_ARDUINO_H__

// Functions for test setup
void setAnalogValue(float value);

// Mock functions
#define INPUT 10

float analogRead(int pin);
void pinMode(int pin, int mode);

#define TFT_WHITE 0
#define TFT_BLACK 1
#define TFT_GREEN 2
#define TFT_YELLOW 3
#define TFT_ORANGE 4
#define TFT_RED 5
#define TFT_PURPLE 6

#endif // __MOCK_ARDUINO_H__