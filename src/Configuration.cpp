#include "Configuration.h"

// Lade Konfigurationen vom EEPROM
Configuration::Load() {
  return EEPROM.get(0, self.config);
}

// Speichere Konfigurationen in den EEPROM
void Configuration::Save() {
  EEPROM.put(0, self.config);
}

