#include "Display.h"
#include <LiquidCrystal_I2C.h> //lib by Frank de Brabander V1.1.2 -> https://github.com/johnrickman/LiquidCrystal_I2C

LiquidCrystal_I2C lcd(LCD_ADDRESS, LCD_COLS, LCD_ROWS);

Display::Display() {
  lcd.init();
  lcd.backlight();// turn on lcd backlight
}

void Display::showMenu(byte selectedItem)
{
  lcd.clear();

  // TODO add
  if (selectedItem == 0) {
    /* Select Menu-Item "pwm value"*/
  } else if (selectedItem == 1) {
    /* Select Menu-Item "delay value"*/
  } else if (selectedItem == 2) {
    /* Select Menu-Item "start welding"*/
  }
}

void Display::showSubmenu(byte selectedItem, uint8_t value)
{
  // Zeile 1 Name des Submenus
  // Zeile 2 Der aktuelle Wert

  lcd.clear();

  // TODO
  if (selectedItem == 1) {
    lcd.setCursor(0,0);
    lcd.print("PWM value");
    lcd.setCursor(0,1);
    lcd.print(value);
  } else if (selectedItem == 2) {
    lcd.setCursor(0,0);
    lcd.print("Delay value");
    lcd.setCursor(0,1);
    lcd.print(value);
  }
}

void Display::showStartWelding(uint8_t pwm, uint8_t gas_follow_up_time, uint8_t gas_lead_time)
{
  lcd.clear();
}
