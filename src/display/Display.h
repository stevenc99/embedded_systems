#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>

#define LCD_ADDRESS 0x3f //LCD1602a uses address 0x3f and not 0x27 !
#define LCD_COLS 16
#define LCD_ROWS 2

class Display {
  public:
    enum class MenuState {
      PWM = 0,
      G_FOL_UP_TIME = 1,
      G_LEAD_TIME = 2,
      START_WELDING = 3,
      NUMBER_OF_STATES = 4
    };

    // ----- Constructor -----
    Display();

    // the selected menu item
    void showMenu(byte selectedItem);

    // Go into the selected menu item
    void showSubmenu(byte selectedItem, uint8_t currentValue);

    // start welding
    void showStartWelding(uint8_t pwm, uint8_t gas_follow_up_time, uint8_t gas_lead_time);

  private:
};

#endif /* DISPLAY_H */