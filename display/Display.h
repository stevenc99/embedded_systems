#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>

enum params = {pwm, delay, u};

// Gibt Text auf dem Display aus
void display(char text[]);

// Zeige alle verfügbaren Menüpunkte
// selectedItem - Markiere (visuell) den aktuellen Menüpunkt
void showMenu(int selectedItem);

// Gehe in den Menüpunkt rein
// selectedItem - Der aktuell ausgewählte Menüpunkt
// 		- 1 = Start Welding
// 		- 2 = PWM
// 		- 3 = Delay
void selectMenu(int selectedItem);

// Ändern der Anzeige nach Inkrement/Dekrement
void updateVoltage();

void updateDelay();

void updatePWM();

// Inkrementiere einen bestimmten Parameter
void incrementValue(params parameter);

void decrementValue(params parameter);

// Abhängig vom aktuellen Zustand,
// leuchten verschiedener LEDs
void updateLedState(char state);

// Starte Schweißvorgang
void startWelding();
// Stoppe Schweißvorgang
void stopWelding();
#endif /* DISPLAY_H */
