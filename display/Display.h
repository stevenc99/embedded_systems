#ifndef DISPLAY
#define DISPLAY

// starte Gerät
// Ausgabe: "Gerät startet"
// pwm 	 - geladener PWM-Wert
// delay - geladener Delay-Wert
// v 	 - geladener Spannungswert
void systemStart(int pwm, int delay, int v);

// Gerät Einsatzbereit
// Ausgabe: "Gerät Einsatzbereit"
void systemReady();

// Zeige Dashboard
void showDashboard();

// Zeige alle verfügbaren Menüpunkte
// selectedItem - Markiere (visuell) den aktuellen Menüpunkt
void showMenu(int selectedItem);

// Gehe in den Menüpunkt rein
// selectedItem - Der aktuell ausgewählte Menüpunkt
// 		- 1 = Start Welding
// 		- 2 = PWM
// 		- 3 = Delay
void selectMenu(int selectedItem);

// Wenn der Benutzer einen Wert ändert (inkrementiert bzw. dekrementiert)
// newValue  	- Der neue Wert, der angezeigt werden soll
void updateValue(int newValue);

#endif /* DISPLAY_H */
