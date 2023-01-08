// https://arduinogetstarted.com/tutorials/arduino-keypad

#include "Input.h" 
#include <Keypad.h> // --> https://github.com/Chris--A/Keypad/tree/master/src

/****************************************
 * NumPad-Only Variante
 ****************************************/

const int ROW_NUM = 4; //four rows
const int COLUMN_NUM = 3; //three columns

char keys[ROW_NUM][COLUMN_NUM] = {
    {'1','2','3'},
    {'4','5','6'},
    {'7','8','9'},
    {'*','0','#'}
};

byte pin_rows[ROW_NUM] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
byte pin_column[COLUMN_NUM] = {5, 4, 3}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM );

char getKey() {
    // NO_KEY = '\0'
    char key = keypad.getKey();
    return key;
}
