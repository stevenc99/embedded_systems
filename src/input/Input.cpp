#include "Input.h"

// Variables to debounce
long time_of_last_rot = 0;
int delay_of_debounce = 100;

long button_time_of_last_rot = 0;

// direction state
int rot_direction = 0;
int prev_rot_direction;

// button state
bool button_state = false;
bool prev_button_state;

// Store current pin state
int current_clk;
int current_dt;

// Store previous pin state
int prev_clk;
int prev_dt;

// counter variable for serial output
int counter;

void encoder() {
    if ((prev_clk == 0) && (prev_dt == 1)) {
        if ((current_clk == 1) && (current_dt == 0)) {
            /* CLOCKWISE */
            rot_direction = 1;
        }
        if ((current_clk == 1) && (current_dt == 1)) {
            /* COUNTERCLOCKWISE */
            rot_direction = -1;
        }
    }
    if ((prev_clk == 1) && (prev_dt == 0)) {
        if ((current_clk == 0) && (current_dt == 1)) {
            /* CLOCKWISE */
            rot_direction = 1;
        }
        if ((current_clk == 0) && (current_dt == 0)) {
            /* COUNTERCLOCKWISE */
            rot_direction = -1;
        }
    }

    if ((prev_clk == 1) && (prev_dt == 1)) {
        if ((current_clk == 0) && (current_dt == 1)) {
            /* CLOCKWISE */
            rot_direction = 1;
        }
        if ((current_clk == 0) && (current_dt == 0)) {
            /* COUNTERCLOCKWISE */
            rot_direction = -1;
        }
    }
    if ((prev_clk == 0) && (prev_dt == 0)) {
        if ((current_clk == 1) && (current_dt == 0)) {
            /* CLOCKWISE */
            rot_direction = 1;
        }
        if ((current_clk == 1) && (current_dt == 1)) {
            /* COUNTERCLOCKWISE */
            rot_direction = -1;
        }
    }
}

void isrRotary() {
    current_clk = digitalRead(PIN_CLK);
    current_dt = digitalRead(PIN_DT);

    if ((millis() - time_of_last_rot) > delay_of_debounce) {
        encoder();
        counter += rot_direction;
        //Serial.print("counter - "); fürs debuggen
        //Serial.println(counter);
        time_of_last_rot = millis();
    }

    prev_clk = current_clk;
    prev_dt = current_dt;
}

void isrButton() {
  if ((millis() - button_time_of_last_rot) > delay_of_debounce) {
        button_state = true;
    }
}

int getDirection() {
    prev_rot_direction = rot_direction;
    rot_direction = 0;
    return prev_rot_direction;
}

bool getButtonState() {
    prev_button_state = button_state;
    button_state = false;
    return prev_button_state;
}

void setupInput() {
    pinMode(PIN_CLK, INPUT);
    pinMode(PIN_DT, INPUT);
    pinMode(PIN_SW, INPUT_PULLUP);

    prev_clk = digitalRead(PIN_CLK);
    prev_dt = digitalRead(PIN_DT);

    attachInterrupt(digitalPinToInterrupt(PIN_CLK), isrRotary, CHANGE);
    attachInterrupt(digitalPinToInterrupt(PIN_SW), isrButton, FALLING);
}