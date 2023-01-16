#ifndef TIMING_H
#define TIMING_H

#include <Arduino.h>

// Starte den Schweißvorgang
// return true when successful
bool startWelding(uint8_t pwm, uint8_t delay);

// Stoppe den Schweißvorgang
// Stelle den sicheren Zustand wieder her
void stopWelding();

#endif /* TIMING_H */