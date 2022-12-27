#include "Display.h"
#include "Input.h"
#include "Menu.h"
#include "Timing.h"

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
char currentState = 0b00000000;

int pwm = 0;
int delay = 0;
int v = 0;

// Lade gespeicherte Parameter-Werte
void loadConfiguration() {
    // TODO
}

// Wird 1x zum Systemstart ausgeführt
// Ist blockierend
void setup() {
    loadConfiguration();
    systemStart(1, 1, 1);
    systemReady();
    // vielleicht noch ein 2 sec Delay
    showDashboard();
}

// Wird ausgeführt, wenn Gerät ausgeschalten wird
void shutOff() {
    // TODO
}

void main() {
    setup();
}

void loop() {
    // TODO
}
