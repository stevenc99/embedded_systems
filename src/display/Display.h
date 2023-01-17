#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>

#define MENU_MAIN_LENGTH 6

void makeDisplayReady();
bool showMenu(int identifier, byte valueNum);

#endif /* DISPLAY_H */