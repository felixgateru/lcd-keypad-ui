#include <Arduino.h>
#include "LiquidCrystal_I2C.h"
#include "Keypad.h"
#include "defs.h"


LiquidCrystal_I2C lcd(0x27, 20, 4);
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);


void keypadEvent(KeypadEvent key);

String inputString;



void setup()
{
    Serial.begin(115200);
    lcd.init();
    lcd.setCursor(4, 1);
    lcd.print("LCD Test V 0.0.1");
    // Store initial LED state. HIGH when LED is on.
    keypad.addEventListener(keypadEvent); // Add an event listener for this keypad
    delay(1000);
    pinMode(LED_BUILTIN, OUTPUT);
    lcd.clear();
    
}

void loop()
{
    char key = keypad.getKey();
    

    if (key)
    {
        lcd.clear();
        Serial.println(key);
        lcd.print(key);
    }

}

// Taking care of some special events.
void keypadEvent(KeypadEvent key)
{
    switch (keypad.getState())
    {
    case PRESSED:
        if (key == 'D')
        {}
       
        else if (key == 'C')
        {
        }
        break;

    case RELEASED:
            if (key == 'D')
            {
            }
            break;
    }
}