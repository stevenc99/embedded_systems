#include "Display.h"
#include <LiquidCrystal_I2C.h> //lib by Frank de Brabander V1.1.2 -> https://github.com/johnrickman/LiquidCrystal_I2C

/*#################################################################
###### Global Definitions
###################################################################*/

LiquidCrystal_I2C lcd(0x3f, 16, 2); //LCD1602a uses address 0x3f and not 0x27 !

#define MENU_MAIN_LENGTH 4

/*#################################################################
###### Global Variables
###################################################################*/

int menuActPos = 0;

//list as strings-array
//pls use max 15 chars, because display shows 15 + 1 chars in one line only! One char is needed to show selected line in menu controls.
String menuMain[MENU_MAIN_LENGTH] = { 
    "pwm value", 
    "delay value", 
    "start welding",
    "stop welding",
};

void setupDisplay() {
  lcd.init();
  lcd.backlight();// turn on lcd backlight
}

void showMenu(byte selectedItem)
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
  
  // TODO delete
  // lcd.setCursor(0,0);
  // rowOne = ">" + rowOne;
  // lcd.print(rowOne);
  // Serial.println(rowOne);
  // lcd.setCursor(0,1);
  // lcd.print(rowTwo);
  // Serial.println(rowTwo);
}

void selectMenu(byte selectedItem, uint8_t value)
{
  // Zeile 1 Name des Submenus
  // Zeile 2 Der aktuelle Wert

  lcd.clear();

  // TODO add
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

void selectMenu(byte selectedItem, uint8_t pwm, uint8_t delay)
{
  lcd.clear();

  // TODO add
  if (selectedItem == 2) {
    // besonderer Zustand "starte Schweißen"
    // hier sollen ausschließlich die Parameter visualisiert werden
    // und nach nochmaligen drücken von * soll der Vorgang beendet werden
  }
}

void updateValue(uint8_t value) {
  // TODO lösche Zeile 2 und füge neuen Wert ein
}
