#ifndef INPUT_H
#define INPUT_H

#include <Arduino.h>

#define PIN_CLK A2 // anpassen
#define PIN_DT A3 // anpassen
#define PIN_SW A4  // anpassen

class Input {
  public:
    enum class Direction {
      NOROTATION = 0,
      CLOCKWISE = 1,
      COUNTERCLOCKWISE = -1
    };

    enum class ButtonState {
      NOACTION = 0,
      PRESSED = 1,
      RELEASED = 2
    };

    // ----- Constructor -----
    Input();

    // retrieve the current Button State
    ButtonState getButtonState();

    // simple retrieve of the direction the knob was rotated last time. 0 = No rotation, 1 = Clockwise, -1 = Counter Clockwise
    Direction getDirection();

  private:
};

#endif /* INPUT_H */
