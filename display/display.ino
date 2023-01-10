#include <LiquidCrystal_I2C.h>        //lib by Frank de Brabander V1.1.2 -> https://github.com/johnrickman/LiquidCrystal_I2C


/*#################################################################
###### Include head files of groups here
###################################################################*/

//#include "DisplayControls.h"


/*#################################################################
###### Global Definitions
###################################################################*/

LiquidCrystal_I2C lcd(0x3f, 16, 2);       //LCD1602a uses address 0x3f and not 0x27 !

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

void showMenu(String rowOne, String rowTwo)
{
  lcd.clear();
  lcd.setCursor(0,0);
  rowOne = ">" + rowOne;
  lcd.print(rowOne);
  Serial.println(rowOne);
  lcd.setCursor(0,1);
  lcd.print(rowTwo);
  Serial.println(rowTwo);
}



void setup() {
  Serial.begin(9600);

  lcd.init();
  lcd.backlight();// turn on lcd backlight
}

void loop()
{
  //Show Menu
  if(menuActPos >= MENU_MAIN_LENGTH)
  {
    menuActPos = 0;
    showMenu(menuMain[4]);
  }
  showMenu(menuMain[menuActPos], menuMain[menuActPos + 1]);
  menuActPos = menuActPos + 1;
  delay(2000);
}