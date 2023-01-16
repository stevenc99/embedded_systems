// https://peppe8o.com/ky-040-and-arduino-rotatory-encoder-wiring-and-code/
// https://github.com/mathertel/RotaryEncoder/blob/master/src/RotaryEncoder.cpp
#include "Input.h"

int lastStateCLK;
int currentStateCLK;
unsigned long lastButtonPress = 0;

// ----- Initialization and Default Values -----

Input::Input() {
  // Setup the input pins and turn on pullup resistor
  pinMode(PIN_CLK, INPUT);   // Set encoder pins as inputs
  pinMode(PIN_DT, INPUT);
  pinMode(PIN_SW, INPUT_PULLUP);

  lastStateCLK = digitalRead(PIN_CLK);  // Read the initial state of CLK
} // Input()

Input::ButtonState Input::getButtonState() {
  int btnState = digitalRead(PIN_SW);
  if (btnState == LOW) {
    if (millis() - lastButtonPress > 50) { // zum entprellen
      Serial.println("Button pressed!");
    }
    lastButtonPress = millis();
  }
} // getButtonState()

Input::Direction Input::getDirection() {
  Input::Direction ret = Direction::NOROTATION;
  currentStateCLK = digitalRead(PIN_CLK);  // Read the current state of CLK
  if (currentStateCLK != lastStateCLK  && currentStateCLK == 1) {
    if (digitalRead(PIN_DT) != currentStateCLK) {
      ret = Direction::COUNTERCLOCKWISE;
    } else {
      ret = Direction::CLOCKWISE;
    }
    Serial.print("Direction: ");
    Serial.print(ret);
    return ret;
  }
  lastStateCLK = currentStateCLK;
} // getDirection()