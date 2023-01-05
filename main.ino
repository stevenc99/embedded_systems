#include "display/Display.h"
//#include "input.h"
#include "EEPROM.h"

//#define DEBUG

struct configuration {
  uint8_t pwm;
  uint8_t delay;
  uint8_t u;
};

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
//char currentState = 0b00000000;
configuration config = {
  128,
  100,
  230
};

// Wird 1x zum Systemstart ausgeführt
// Ist blockierend
void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ;  // wait for serial port to connect. Needed for native USB port only
  }
  char message[] = "Lade Konfiguration";
  display(message);

  config = loadConfiguration();
#ifdef DEBUG
  Serial.println("Read custom object from EEPROM: ");
  Serial.println(config2.pwm);
  Serial.println(config2.delay);
  Serial.println(config2.u);
#endif

  char message2[] = "Einsatzbereit";
  display(message2);
  displayConfig
}

void loop() {
  // TODO
}

// speichert momentan eingestellten Werte für pwm, delay und u
// pwm:       0 .. 255
// delay(ms): 0 .. 255 -> (multiplizieren für höherere Delays)
// u(V):      0 .. 255
void saveConfiguration(configuration config) {
  // An EEPROM write takes 3.3 ms to complete.
  EEPROM.put(0, config);
}

// Konfiguration steht immer an Adresse 0
configuration loadConfiguration() {
  return EEPROM.get(0, config);
}

void shutDown() {
  /* TODO
   input des on-off-switches auswerten
   aktuelle pwm = 0 setzen
   schutzgas ventil schließen
   Konfiguration speichern
  */
}
