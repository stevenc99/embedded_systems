#include <EEPROM.h>
#include "input/Input.h"
#include "display/Display.h"
#include "timing/Timing.h"

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

// Zustandskontrolle für das Menu
// 0, wenn "pwm" ausgewählt
// 1, wenn "delay" ausgewählt
// 2, wenn "start welding" ausgewählt
byte selectedItem = 0;

// Zustandskontrolle für das Menu
// - false, wenn nichts ausgewählt
// - true, wenn man sich im aktuell selektierten Menubereich befindet
bool activeMenuItem = false;

// struct für die Konfigurationswerte
struct configuration {
  uint8_t pwm;
  uint8_t delay;
};
configuration config;

// neuer Wert für die Konfigurationswerte
String newValue;

// Lade Konfigurationen vom EEPROM
configuration loadConfiguration() {
  return EEPROM.get(0, config);
}

// Speichere Konfigurationen in den EEPROM
void saveConfiguration() {
  EEPROM.put(0, config);
}

// Navigation des Menus
void menuNavigation(char key) {
  // Menu Navigation
  switch (key) {
    case '1':
      /* pwm */
      selectedItem = 0;
      showMenu(selectedItem);
      break;
    case '2':
      /* delay */
      selectedItem = 1;
      showMenu(selectedItem);
      break;
    case '3':
      /* start welding */
      selectedItem = 2;
      showMenu(selectedItem);
      break;
    case '*':
      /* select current item */
      switch (selectedItem) {
        case 0:
          /* pwm */
          selectMenu(selectedItem, config.pwm);
          break;
        case 1:
          /* delay */
          selectMenu(selectedItem, config.delay);
          break;
        case 2:
          /* start welding */
          selectMenu(selectedItem, config.pwm, config.delay);
          break;
      } // switch(selectedItem)
      activeMenuItem = true;
      break;
    case '#':
      /* shut down */
      shutDown();
      break;
  } // switch(key)
}

// Submenu Navigation
void submenuNavigation(char key) {
  if (key == '*') {
    // go back and save
    // TODO prüfe ob es ein zulässiger Wert ist
    switch (selectedItem) {
      case 0:
        /* pwm */
        config.pwm = (uint8_t)newValue.toInt();
        break;
      case 1:
        /* delay */
        config.delay = (uint8_t)newValue.toInt();
        break;
      case 2:
        /* stop welding */
        break;
    } // switch(selectedItem)
    activeMenuItem = false;
    showMenu(selectedItem);
  } else if (key == '#') {
    /* go back without saving */
    activeMenuItem = false;
    showMenu(selectedItem);
  } else {
    // append new value
    if (selectedItem != 2) { // Während des Schweißens keine Werte ändern (falls doch -> anpassen)
      if (newValue.length() == 3) {
        /* reset */
        newValue = "";
      }
      newValue += key;
      updateValue(newValue);
    }
  }
}

// Stelle sicheren Zustand wieder her
// und schalte das Gerät aus
void shutDown() {
  /* TODO
   input des on-off-switches auswerten
   aktuelle pwm = 0 setzen
   schutzgas ventil schließen
   Konfiguration speichern
  */
}

void setup() {
  Serial.begin(9600);
  newValue.reserve(2); // maximum input characters is 3, change if needed
  config = loadConfiguration();
  setupDisplay();
  current_state = current_state | 0b00000001; // Gerät Einsatzbereit
  showMenu(selectedItem);
}

void loop() {
  char key = getKey();
  if (key) {
    if (activeMenuItem == false) {
      menuNavigation(key);
    } else { // activeMenuItem == true
      submenuNavigation(key);
      if (selectedItem == 2 && (current_state & 0b00000010) == false) {
        /* wenn Schweiß-Modus aktiviert werden soll */
        bool activated = startWelding(config.pwm, config.delay);
        if (activated) {
          current_state = current_state | 0b00000010; // Schweiß-Modus aktiviert
        }
      } else if ((current_state & 0b00000010) == true && ((key == '#') || (key == '*'))) {
        /* wenn Schweiß-Modus deaktiviert werden soll */
        bool deactivated = stopWelding();
        if (deactivated) {
          current_state = current_state & 0b11111101; // Schweiß-Modus deaktiviert
        }
      }
    }
  }
}
