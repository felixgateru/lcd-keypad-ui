#ifndef PIN_CONFIGURATIONS_H
#define PIN_CONFIGURATIONS_H

#include <Arduino.h>



const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
    {'D','#','0', '*'},
    {'C','9','8', '7'},
    {'B','6','5', '4'},
    {'A','3','2', '1'}
}; 

byte rowPins[ROWS] = {2, 4, 16, 17}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 18, 19,23}; //connect to the column pinouts of the keypad





#endif