#ifndef INPUT_H
#define INPUT_H

#include <Arduino.h>

#define PIN_CLK 2
#define PIN_DT 4
#define PIN_SW 3

void setupInput();

int getDirection();
bool getButtonState();

#endif /* INPUT_H */