#ifndef TIMING_H
#define TIMING_H

#include <Arduino.h>

uint8_t welding(uint8_t current_state, uint8_t pwm, uint8_t gas_follow_up_time, uint8_t gas_lead_time, int pin);

#endif /* TIMING_H */
