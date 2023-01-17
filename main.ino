#include "src/input/Input.h"
#include "src/display/Display.h"
#include "src/config/Config.h"


/*********************************************************
 * system state
**********************************************************/

// bit0 (LED)
// - 0, wenn Gerät nicht Einsatzbereit (aus oder startet)
// - 1, wenn Gerät Einsatzbereit
// bit1 (LED)
// - 0, wenn Schweiß-Modus deaktiviert
// - 1, wenn Schweiß-Modus aktiviert
// bit2 (LED)
// - 0, wenn Ventil zu
// - 1, wenn Ventil offen
// bit3 (LED)
// - 0, wenn Drahtvorschub inaktiv
// - 1, wenn Drahtvorschub aktiv
// bit4 (LED)
// - 0, wenn bearbeitung inaktiv
// - 1, wenn bearbeitung aktiv
// bit5 (LED)
// - 0, wenn kein Error
// - 1, wenn Error
byte current_state = 0b00000000;


/*********************************************************
 * menu state
**********************************************************/

// Zustandskontrolle für das Menu
byte menuPointerPosition = 0;


/*********************************************************
 * configuration
**********************************************************/

Config config;


/*********************************************************
 * functions
**********************************************************/

void buttonPressed(bool buttonState) {
  if (buttonState) {
    if ((current_state & 0b00000010) = true) { // Wenn Schweiß-Modus aktiviert
      // TODO Schweiß-Modus deaktivieren
      // TODO LEDs aktualisieren
      current_state = current_state & 0b11111101;
      showMenu(menuPointerPosition%MENU_MAIN_LENGTH, config.getValue(menuPointerPosition%MENU_MAIN_LENGTH));
    } else if (menuPointerPosition%MENU_MAIN_LENGTH == 0) { // Wenn Schweiß-Modus deaktiviert
      // TODO Schweiß-Modus aktivieren
      // TODO LEDs aktualisieren
      current_state = current_state | 0b00000010;
      menuPointerPosition = 4; // zeige "stop welding"
      showMenu(menuPointerPosition%MENU_MAIN_LENGTH, config.getValue(menuPointerPosition%MENU_MAIN_LENGTH));
    }
    
    if ((current_state & 0b00010000) = true) { // Wenn bearbeiten aktiviert
      // bearbeiten deaktivieren
      // TODO LEDs aktualisieren
      current_state = current_state & 0b11101111;
    } else if (menuPointerPosition%MENU_MAIN_LENGTH != 0) { // Wenn bearbeiten deaktiviert
      // bearbeiten aktivieren
      // TODO LEDs aktualisieren
      current_state = current_state | 0b00010000;
    }
  }
}

void rotDirection(int directionState) {
  if (((current_state & 0b00010010) = false) && (directionState != 0)) {
    /* navigiere durch das Menu */
    menuPointerPosition += directionState;
    showMenu(menuPointerPosition%MENU_MAIN_LENGTH, config.getValue(menuPointerPosition%MENU_MAIN_LENGTH));
  } else if (((current_state & 0b00010000) = true) && (directionState != 0)) {
    /* Increment/Decrement values */
    config.setValue(menuPointerPosition%MENU_MAIN_LENGTH, directionState);
    showMenu(menuPointerPosition%MENU_MAIN_LENGTH, config.getValue(menuPointerPosition%MENU_MAIN_LENGTH));
  }
}


/*********************************************************
 * setup & loop
**********************************************************/

void setup() {
  Serial.begin(9600);
  //config.Load();

  makeDisplayReady();
  setupInput();

  current_state = current_state | 0b00000001; // Gerät Einsatzbereit
  // TODO LEDs aktualisieren
  showMenu(menuPointerPosition%MENU_MAIN_LENGTH, config.getValue(menuPointerPosition%MENU_MAIN_LENGTH));
}

void loop() {
  // prüfe auf Eingabe
  bool buttonState = getButtonState();
  int directionState = getDirection();
  
  buttonPressed(buttonState);
  rotDirection(directionState);
}
