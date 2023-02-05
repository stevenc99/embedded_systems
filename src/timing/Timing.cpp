#include "Timing.h"

long prev_sys_time;
uint8_t multiplier = 100; // 0 bis 25.5 sec


uint8_t welding(uint8_t current_state, uint8_t pwm, uint8_t gas_follow_up_time, uint8_t gas_lead_time, int pin) {
  uint8_t new_state = current_state;

  /* starte Prozess */
  if ( (current_state & 0b00000010) && !(current_state & 0b00000100) ) { // Wenn Schweiß-Modus aktiviert & Ventil geschlossen
    Serial.println("öffne Ventil");
    new_state = current_state | 0b00000100;
    prev_sys_time = millis();
  }
  if ( ((current_state & 0b00000110) == 0b00000110) && !(current_state & 0b00001000) ) { // Wenn Schweiß-Modus aktiviert & Ventil offen & Drahtvorschub inaktiv
    if ( (millis() - prev_sys_time) >= (gas_follow_up_time * multiplier) ) { // warte x millisec (gasvorlauf)
      Serial.println("starte Drahtvorschub");
      Serial.print("PWM-Leistung: ~");
      Serial.print((float) ( (0.39) * ((float)pwm) ));
      Serial.println("%");
      analogWrite(pin, pwm);
      new_state = current_state | 0b00001000;
    }
  }
  
  /* stoppe Prozess */
  if ( !(current_state & 0b00000010) && (current_state & 0b00001000) ) { // Wenn Schweiß-Modus deaktiviert & Drahtvorschub aktiv
    Serial.println("stoppe Drahtvorschub");
    analogWrite(pin, 0);
    new_state = current_state & 0b11110111;
    prev_sys_time = millis();
  }
  if ( ((current_state & 0b00001010) == 0) && (current_state & 0b00000100) ) { // Wenn Schweiß-Modus deaktiviert & Drahtvorschub inaktiv & Ventil offen
    if ( (millis() - prev_sys_time) >= (gas_lead_time * multiplier) ) { // warte x millisec (gasnachlauf)
      Serial.println("schließe Ventil");
      new_state = current_state & 0b11111011;
    }
  }

  return new_state;
}
