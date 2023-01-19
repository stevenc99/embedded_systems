#include "Config.h"

// Lade Konfigurationen vom EEPROM
void Config::Load() {
  int address = 0;
  EEPROM.get(address, pwm);
  Serial.print("address = ");
  Serial.println(address);
  Serial.print("PWM = ");
  Serial.println(pwm);
  address += sizeof(uint8_t);
  EEPROM.get(address, gas_follow_up_time);
  Serial.print("address = ");
  Serial.println(address);
  Serial.print("gas_follow_up_time = ");
  Serial.println(gas_follow_up_time);
  address += sizeof(uint8_t);
  EEPROM.get(address, gas_lead_time);
  Serial.print("address = ");
  Serial.println(address);
  Serial.print("gas_lead_time = ");
  Serial.println(gas_lead_time);
  Serial.println("Load");
}

// Speichere Konfigurationen in den EEPROM
void Config::Save() {
  Serial.println("Save");
  int address = 0;
  EEPROM.update(address, pwm);
  Serial.print("address = ");
  Serial.println(address);
  Serial.print("PWM = ");
  Serial.println(pwm);
  address += sizeof(uint8_t);
  EEPROM.update(address, gas_follow_up_time);
  Serial.print("address = ");
  Serial.println(address);
  Serial.print("gas_follow_up_time = ");
  Serial.println(gas_follow_up_time);
  address += sizeof(uint8_t);
  EEPROM.update(address, gas_lead_time);
  Serial.print("address = ");
  Serial.println(address);
  Serial.print("gas_lead_time = ");
  Serial.println(gas_lead_time);
  Serial.println("Save");
}