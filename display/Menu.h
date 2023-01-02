#ifndef MENU_H
#define MENU_H

// Wenn der Benutzer einen neuen Wert speichern möchte
// type 	- welcher Wert aktualisiert wird (PWM, Delay, ...)
// newValue - Der neue Wert, der gespeichert werden soll
void saveValue(int pwm, int delay, int v);
// Inkrementiere einen bestimmten Wert
// type - welcher Wert aktualisiert wird (PWM, Delay, ...)
void incrementValue(int type);
// Dekrementiere einen bestimmten Wert
// type - welcher Wert aktualisiert wird (PWM, Delay, ...)
void decrementValue(int type);
// Starte Schweißvorgang
void startWelding();
// Stoppe Schweißvorgang
void stopWelding();

#endif /* MENU_H */
