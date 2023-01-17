#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>
#include <EEPROM.h>

class Config {
    private:
        uint8_t pwm = 0;
        uint8_t gas_follow_up_time = 0; // gasnachlaufzeit
        uint8_t gas_lead_time = 0;      // gasvorlaufzeit

    public:
        void Save();
        void Load();

        void SetPWM(uint8_t p) { this->pwm = p; };
        uint8_t GetPWM() { return this->pwm; };

        void SetGasFollowUpTime(uint8_t f) { this->gas_follow_up_time = f; };
        uint8_t GetGasFollowUpTime() { return this->gas_follow_up_time; };

        void SetGasLeadTime(uint8_t l) { this->gas_lead_time = l; };
        uint8_t GetGasLeadTime() { return this->gas_lead_time; };

        uint8_t getValue(uint8_t menuPointerPosition) {
            if (menuPointerPosition == 1) {
                return this->pwm;
            } else if (menuPointerPosition == 2) {
                return this->gas_follow_up_time;
            } else if (menuPointerPosition == 3) {
                return this->gas_lead_time;
            } else {
                return 0;
            }
        };

        void setValue(uint8_t menuPointerPosition, int v) {
            if (menuPointerPosition == 1) {
                this->pwm += v;
            } else if (menuPointerPosition == 2) {
                this->gas_follow_up_time += v;
            } else if (menuPointerPosition == 3) {
                this->gas_lead_time += v;
            }
        };
};

#endif /* CONFIG_H */
