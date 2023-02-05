#include "src/input/Input.h"
#include "src/display/Display.h"
#include "src/config/Config.h"
#include "src/timing/Timing.h"

// PIN-Belegung für die LEDs
const int LED_PINS[] = {8, 9, 10, 11, 12, 13};

/*********************************************************
 * system state
**********************************************************/

// bit1 (LED 8)
// - 0, wenn Gerät nicht Einsatzbereit (aus oder startet)
// - 1, wenn Gerät Einsatzbereit
// bit2 (LED 9)
// - 0, wenn Schweiß-Modus deaktiviert
// - 1, wenn Schweiß-Modus aktiviert
// bit3 (LED 10)
// - 0, wenn Ventil zu
// - 1, wenn Ventil offen
// bit4 (LED 11)
// - 0, wenn Drahtvorschub inaktiv
// - 1, wenn Drahtvorschub aktiv
// bit5 (LED 12)
// - 0, wenn bearbeitung inaktiv
// - 1, wenn bearbeitung aktiv
// bit6 (LED 13)
// - 0, wenn kein Error
// - 1, wenn Error
uint8_t current_state = 0b00000000;
uint8_t new_state = current_state;


/*********************************************************
 * menu state
**********************************************************/

// Zustandskontrolle für das Menu
uint8_t menuPointerPosition = 0;


/*********************************************************
 * configuration
**********************************************************/

Config config;


/*********************************************************
 * functions
**********************************************************/

void updateLEDs() {
  if (new_state != current_state) {
    for (uint8_t i = 0; i < 5; i++) {
      if ((current_state & (0b00000001 << i)) && (i != 3)) {
        digitalWrite(LED_PINS[i], HIGH);
        Serial.print("LED ");
        Serial.print(LED_PINS[i]);
        Serial.print(" - ON | ");
      } else if (i != 3) {
        digitalWrite(LED_PINS[i], LOW);
        Serial.print("LED ");
        Serial.print(LED_PINS[i]);
        Serial.print(" - OFF | ");
      }
      if ((current_state & (0b00000001 << i)) && (i == 3)) {
        Serial.print("LED ");
        Serial.print(LED_PINS[i]);
        Serial.print(" - ON | ");
      } else if (i == 3) {
        Serial.print("LED ");
        Serial.print(LED_PINS[i]);
        Serial.print(" - OFF | ");
      }
    }
    new_state = current_state;
    Serial.print("current_state: ");
    Serial.println(current_state);
  }
}

void buttonPressed(bool buttonState) {
  if (buttonState) {
    /* Schweiß-Modus aktivieren und deaktivieren */
    if ((current_state & 0b00001110) == 0b00001110) { // Wenn Schweiß-Modus aktiviert
      Serial.println("Schweiß-Modus deaktivieren");
      current_state = current_state & 0b11111101;
    } else if ((menuPointerPosition%MENU_MAIN_LENGTH == 0) && ((current_state & 0b00001110) == 0)) { // Wenn Schweiß-Modus deaktiviert
      Serial.println("Schweiß-Modus aktivieren");
      current_state = current_state | 0b00000010;
    }
    
    /* Bearbeitung aktivieren und deaktivieren */
    if ((current_state & 0b00010000)) { // Wenn bearbeiten aktiviert
      Serial.println("bearbeiten deaktivieren");
      current_state = current_state & 0b11101111;
    } else if ((menuPointerPosition%MENU_MAIN_LENGTH > 0) && (menuPointerPosition%MENU_MAIN_LENGTH < 4)) { // Wenn pointer auf einem bearbeitbaren Feld
      Serial.println("bearbeiten aktivieren");
      current_state = current_state | 0b00010000;
    }

    /* Speichern */
    if ((menuPointerPosition%MENU_MAIN_LENGTH == 4)) {
      Serial.println("Werte gespeichert");
      config.Save();
    }
  }
}

void rotDirection(int directionState) {
  if (((current_state & 0b00011110) == 0) && (directionState != 0) ) { // Wenn Schweiß-Modus und Bearbeiten deaktiviert
    /* navigiere durch das Menu */
    menuPointerPosition = (menuPointerPosition + directionState) % MENU_MAIN_LENGTH;
    showMenu(menuPointerPosition%MENU_MAIN_LENGTH, config.getValue(menuPointerPosition%MENU_MAIN_LENGTH));
  } else if ((current_state & 0b00010000) && (directionState != 0)) { // Wenn bearbeiten aktiviert
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

  config.Load();

  makeDisplayReady();
  setupInput();
  
  pinMode(LED_PINS[0], OUTPUT);
  pinMode(LED_PINS[1], OUTPUT);
  pinMode(LED_PINS[2], OUTPUT);
  pinMode(LED_PINS[3], OUTPUT);
  pinMode(LED_PINS[4], OUTPUT);
  pinMode(LED_PINS[5], OUTPUT);

  current_state = current_state | 0b00000001; // Gerät Einsatzbereit
  showMenu(menuPointerPosition%MENU_MAIN_LENGTH, 0);
  Serial.println("Gerät Einsatzbereit");
}

void loop() {
  /* prüfe auf Eingabe */
  bool buttonState = getButtonState();
  int directionState = getDirection();
  buttonPressed(buttonState);
  rotDirection(directionState);

  /* Schweißen starten und stopen */
  current_state = welding(current_state, config.getValue(1), config.getValue(2), config.getValue(3), LED_PINS[3]);

  /* Update LEDs */
  updateLEDs();

  /* Springe zum Menupunkt */
  if ( ((current_state & 0b00001110) == 0b00001110) && (menuPointerPosition == 0) ) { // wenn Schweiß-Modus aktiviert & Ventil offen & Drahtvorschub aktiv
    // menuPointer "start welding" -> "stop welding"
    menuPointerPosition = 5;
    showMenu(menuPointerPosition, 0);
  }
  if ( ((current_state & 0b00001110) == 0) && (menuPointerPosition == 5) ) { // wenn Schweiß-Modus deaktiviert & Ventil zu & Drahtvorschub inaktiv
    // menuPointer  "stop welding" -> "start welding"
    menuPointerPosition = 0;
    showMenu(menuPointerPosition, 0);
  }
}
