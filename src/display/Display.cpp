#include "Display.h"
#include <LiquidCrystal_I2C.h>      //lib by Frank de Brabander V1.1.2 -> https://github.com/johnrickman/LiquidCrystal_I2C

LiquidCrystal_I2C lcd(0x3f, 16, 2);

String menuMain[MENU_MAIN_LENGTH] = {
  "start welding", 
  "pwm values", 
  "delay value", 
  "start welding",
  "stop welding",
  "save values"
};

void makeDisplayReady()
{
  lcd.init();
  lcd.backlight();// turn on lcd backlight
  lcd.clear();
}

bool showMenu(int identifier, byte valueNum)
{  
  lcd.clear();
  if(MENU_MAIN_LENGTH > identifier)
  {
    //transformToString(valueNum);

    lcd.setCursor(0,0);
    lcd.print(menuMain[identifier]);
    // if(ifDebugAllow == true) {
    //   Serial.print("line 1: ");
    //   Serial.println(menuMain[identifier]);
    // }
    lcd.setCursor(0,1);
    lcd.print(valueNum);
    // if(ifDebugAllow == true){
    //   Serial.print("line 2: ");
    //   Serial.println(valueNum);
    // }
  return true;
  }
  else {
    lcd.setCursor(0,0);
    lcd.print("Error");
    return false;
  }
}