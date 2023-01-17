#include "Config.h"

// Lade Konfigurationen vom EEPROM
void Config::Load() {
  return EEPROM.get(0, self.config);
}

// Speichere Konfigurationen in den EEPROM
void Config::Save() {
  EEPROM.put(0, self.config);
}