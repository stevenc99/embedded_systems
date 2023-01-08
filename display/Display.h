#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>

// Setup Display
void setupDisplay();

// Show the menu and highlight
// the selected menu item
void showMenu(byte selectedItem);

// Go into the selected menu item
// (pwm | delay)
void selectMenu(byte selectedItem, uint8_t value);

// Go into the selected menu item
// (start welding)
void selectMenu(byte selectedItem, uint8_t pwm, uint8_t delay);

// Update the value of row 2
void updateValue(uint8_t value)

#endif /* DISPLAY_H */
