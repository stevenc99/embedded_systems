#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>

#define MENU_MAIN_LENGTH 5

void makeDisplayReady();
bool showMenu(int identifier, uint8_t valueNum);

#endif /* DISPLAY_H */
