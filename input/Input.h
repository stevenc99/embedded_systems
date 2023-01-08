#ifndef INPUT_H
#define INPUT_H

#include <Arduino.h>

/****************************************
 * Wenn im Menu:
 * - 1 bis 3 selektieren der Menüpunkte
 * - * zum bestätigen
 * 
 * Wenn Parameter-Wert geändert wird:
 * - 0 bis 9 Eingabe der neuen Werte
 * - * zum bestätigen
 * 
 * Wenn im Schweißprozess
 * - * zum beenden
 ****************************************/

// get pressed Key
char getKey();

#endif /* INPUT_H */
