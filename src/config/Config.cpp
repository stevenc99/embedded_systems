#include "Config.h"
#include <EEPROM.h>

// Lade Konfigurationen vom EEPROM
void Config::Load() {
  int address = 0;
  EEPROM.get(address, pwm);
  address += sizeof(uint8_t);
  EEPROM.get(address, gas_follow_up_time);
  address += sizeof(uint8_t);
  EEPROM.get(address, gas_lead_time);
}

// Speichere Konfigurationen in den EEPROM
void Config::Save() {
  Serial.println("Save");
  int address = 0;
  EEPROM.update(address, pwm);
  address += sizeof(uint8_t);
  EEPROM.update(address, gas_follow_up_time);
  address += sizeof(uint8_t);
  EEPROM.update(address, gas_lead_time);
}
