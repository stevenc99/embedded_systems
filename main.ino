#include "src/input/Input.h"
#include "src/display/Display.h"
#include "src/config/Config.h"

// PIN-Belegung für die LEDs
const int LED_PINS[] = {8, 9, 10, 11, 12, 13}; // anpassen
long prev_sys_time;

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

void updateLEDs(byte state) {
  for (byte i = 0; i < 5; i++) {
    if ((state & (0b00000001 << i))) {
      digitalWrite(LED_PINS[i], HIGH);
    } else {
      digitalWrite(LED_PINS[i], LOW);
    }
  }
}

void buttonPressed(bool buttonState) {
  if (buttonState) {
    Serial.println("Button pressed");
    if ((current_state & 0b00001000)) { // Wenn Schweiß-Modus aktiviert
      Serial.println("Schweiß-Modus deaktivieren");
      // Schweiß-Modus deaktivieren
      current_state = current_state & 0b11111101;
      // showMenu(menuPointerPosition%MENU_MAIN_LENGTH, config.getValue(menuPointerPosition%MENU_MAIN_LENGTH)); // TODO show "waiting"?
    } else if ((menuPointerPosition%MENU_MAIN_LENGTH == 0) && (menuPointerPosition%MENU_MAIN_LENGTH != 4) && !(current_state & 0b00000100)) { // Wenn Schweiß-Modus deaktiviert
      Serial.println("Schweiß-Modus aktivieren");
      // Schweiß-Modus aktivieren
      current_state = current_state | 0b00000010;
      updateLEDs(current_state);
      // showMenu(menuPointerPosition%MENU_MAIN_LENGTH, config.getValue(menuPointerPosition%MENU_MAIN_LENGTH)); // TODO show "waiting"?
    }
    
    if ((current_state & 0b00010000)) { // Wenn bearbeiten aktiviert
      Serial.println("bearbeiten deaktivieren");
      // bearbeiten deaktivieren
      current_state = current_state & 0b11101111;
      updateLEDs(current_state);
    } else if ((menuPointerPosition%MENU_MAIN_LENGTH != 0) && (menuPointerPosition%MENU_MAIN_LENGTH != 5) && (menuPointerPosition%MENU_MAIN_LENGTH != 4)) { // Wenn bearbeiten deaktiviert && wenn menupointerposition != 5 (-> stop welding)
      Serial.println("bearbeiten aktivieren");
      // bearbeiten aktivieren
      current_state = current_state | 0b00010000;
      updateLEDs(current_state);
    }

    if ((menuPointerPosition%MENU_MAIN_LENGTH == 4)) {
      config.Save();
    }
  }
}

void rotDirection(int directionState) {
  if (!(current_state & 0b00011110) && (directionState != 0) ) { // Wenn Schweiß-Modus deaktiviert && 
    Serial.println("Navigate through menu");
    /* navigiere durch das Menu */
    menuPointerPosition += directionState;
    showMenu(menuPointerPosition%MENU_MAIN_LENGTH, config.getValue(menuPointerPosition%MENU_MAIN_LENGTH));
  } else if ((current_state & 0b00010000) && (directionState != 0)) {
    Serial.println("Change Value");
    /* Increment/Decrement values */
    config.setValue(menuPointerPosition%MENU_MAIN_LENGTH, directionState);
    showMenu(menuPointerPosition%MENU_MAIN_LENGTH, config.getValue(menuPointerPosition%MENU_MAIN_LENGTH));
  }
}

void welding() {
  /* starte Prozess */
  if ( (current_state & 0b00000010) && !(current_state & 0b00000100) ) { // Wenn Schweiß-Modus aktiviert & Ventil geschlossen
    Serial.println("öffne Ventil");
    // öffne Ventil
    current_state = current_state | 0b00000100;
    updateLEDs(current_state);
    prev_sys_time = millis();
  }
  if ( (current_state & 0b00000010) && !(current_state & 0b00001000) ) { // Wenn Schweiß-Modus aktiviert & Drahtvorschub inaktiv
    if ( (millis() - prev_sys_time) >= (config.getValue(2) * 100) ) { // warte x sec (gasvorlauf)
      Serial.println("starte Drahtvorschub");
      // starte Drahtvorschub
      // TODO PWM
      current_state = current_state | 0b00001000;
      updateLEDs(current_state);
      menuPointerPosition = 5; // zeige "stop welding"
      showMenu(menuPointerPosition, config.getValue(menuPointerPosition%MENU_MAIN_LENGTH));
    }
  }
  
  /* stoppe Prozess */
  if ( !(current_state & 0b00000010) && (current_state & 0b00001000) ) { // Wenn Schweiß-Modus deaktiviert & Drahtvorschub aktiv
    // stoppe Drahtvorschub
    Serial.println("stoppe Drahtvorschub");
    current_state = current_state & 0b11110111;
    updateLEDs(current_state | 0b00000010); // LED 1 später ausschalten
    prev_sys_time = millis();
  }
  if ( !(current_state & 0b00000010) && (current_state & 0b00000100) ) { // Wenn Schweiß-Modus deaktiviert & Ventil offen
    if ( (millis() - prev_sys_time) >= (config.getValue(3) * 100) ) { // warte x sec (gasnachlauf)
      // schließe Ventil
      Serial.println("schließe Ventil");
      current_state = current_state & 0b11111011;
      updateLEDs(current_state);
      menuPointerPosition = 0; // zeige "start welding"
      showMenu(menuPointerPosition%MENU_MAIN_LENGTH, config.getValue(menuPointerPosition%MENU_MAIN_LENGTH));
    }
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
  showMenu(menuPointerPosition%MENU_MAIN_LENGTH, config.getValue(menuPointerPosition%MENU_MAIN_LENGTH));

  updateLEDs(current_state);
}

void loop() {
  // prüfe auf Eingabe
  bool buttonState = getButtonState();
  int directionState = getDirection();
  
  if (!(buttonState && (directionState != 0))) {
    buttonPressed(buttonState);
    rotDirection(directionState);
  }

  welding();
}
