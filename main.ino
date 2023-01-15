#include <EEPROM.h>
#include "input/Input.h"
#include "display/Display.h"

/*********************************************************
 * Instances
**********************************************************/

// A pointer to the dynamic created input instance.
// This will be done in setup()
Input *inputInstance = nullptr;
Input *displayInstance = nullptr;


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
// - 0, wenn kein Error
// - 1, wenn Error
byte current_state = 0b00000000;


/*********************************************************
 * menu state
**********************************************************/

// Zustandskontrolle für das Menu
// 0, wenn "pwm" ausgewählt
// 1, wenn "gasnachlaufzeit" ausgewählt
// 2, wenn "gasvorlaufzeit" ausgewählt
// 3, wenn "start welding" ausgewählt
byte menuPointerPosition = 0;

// Zustandskontrolle für das Menu
// - false, wenn nichts ausgewählt
// - true, wenn man sich im aktuell selektierten Menubereich befindet
bool activeMenuItem = false;


/*********************************************************
 * configuration
**********************************************************/

// struct für die Konfigurationswerte
struct configuration {
  uint8_t pwm;
  uint8_t gas_follow_up_time; // gasnachlaufzeit
  uint8_t gas_lead_time;      // gasvorlaufzeit
};
configuration config;

// Lade Konfigurationen vom EEPROM
configuration loadConfiguration() {
  return EEPROM.get(0, config);
}

// Speichere Konfigurationen in den EEPROM
void saveConfiguration() {
  EEPROM.put(0, config);
}


/*********************************************************
 * setup & loop
**********************************************************/

void setup() {
  Serial.begin(9600);
  config = loadConfiguration();

  displayInstance = new Display();
  inputInstance = new Input();

  current_state = current_state | 0b00000001; // Gerät Einsatzbereit
  displayInstance->showMenu(menuPointerPosition);
}

void loop() {
  // prüfe auf Eingabe
  Input::ButtonState buttonState = inputInstance->getButtonState();
  Input::Direction directionState = inputInstance->getDirection();
  
  buttonPressed(buttonState);
  rotDirection(directionState);
}


/*********************************************************
 * functions
**********************************************************/

void buttonPressed(Input::ButtonState buttonState) {
  if (!activeMenuItem) {
    /* enter submenu */
    displayInstance->showSubmenu(menuPointerPosition);
  } else {
    /* go back */
    displayInstance->showMenu(menuPointerPosition);
  }
}

void rotDirection(Input::Direction directionState) {
  if (!activeMenuItem) {
    /* Menu Navigation */
    switch (directionState) {
      case Input::Direction::COUNTERCLOCKWISE: /* go up */
        menuPointerPosition = (menuPointerPosition-1)%Display::MenuState::NUMBER_OF_STATES;
        break;
      case Input::Direction::CLOCKWISE: /* go down */
        menuPointerPosition = (menuPointerPosition+1)%Display::MenuState::NUMBER_OF_STATES;
        break;
      default:
        break;
    } // switch(directionState)
    displayInstance->showMenu(menuPointerPosition);
  } else {
    /* Increment/Decrement values */
    switch (menuPointerPosition) {
      case 0:
        /* pwm */
        config.pwm += directionState;
        displayInstance->showSubmenu(menuPointerPosition, config.pwm);
        break;
      case 1:
        /* gasnachlaufzeit */
        config.gas_follow_up_time += directionState;
        displayInstance->showSubmenu(menuPointerPosition, config.gas_follow_up_time);
        break;
      case 2:
        /* gasvorlaufzeit */
        config.gas_lead_time += directionState;
        displayInstance->showSubmenu(menuPointerPosition, config.gas_lead_time);
        break;
      case 3:
        /* Schweiß-Modus deaktivieren */
        if (directionState != 0) {
          current_state = current_state & 0b11111101;
          activeMenuItem = false;
          displayInstance->showMenu(menuPointerPosition);
        }
        break;
      default:
        break;
    } // switch(menuPointerPosition)
  }
}
