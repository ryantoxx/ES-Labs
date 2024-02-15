#include <Keypad.h>
#include <LiquidCrystal.h>

#define RED_LED_PIN 13
#define GREEN_LED_PIN 12

const int ROW_NUM    = 4; 
const int COLUMN_NUM = 4; 

char keys[ROW_NUM][COLUMN_NUM] = {
  {'1','2','3', 'A'},
  {'4','5','6', 'B'},
  {'7','8','9', 'C'},
  {'*','0','#', 'D'}
};

byte pin_rows[ROW_NUM] = {9, 8, 7, 6};      
byte pin_column[COLUMN_NUM] = {5, 4, 3, 2}; 

Keypad keypad = Keypad(makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM );

const int RS = A5, EN = A4, D4 = A3, D5 = A2, D6 = A1, D7 = A0;
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

int cursorColumn = 0;
int cursorRow = 0;

String validCode = "1A2B";
String currentCode;

unsigned long previousMillis = 0;
const long interval = 1000;

void setup(){
  lcd.begin(16, 2);

  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
}

void loop(){
  char key = keypad.getKey();

  if (key) {
    lcd.setCursor(cursorColumn, cursorRow); 
    lcd.print(key);                
    currentCode += key;

    cursorColumn++;                 

    if (cursorColumn == 4) {
      int ledPin;

      if (currentCode == validCode) {
        ledPin = GREEN_LED_PIN;
      } else {
        ledPin = RED_LED_PIN;
      }

      digitalWrite(ledPin, HIGH);
      previousMillis = millis();

      lcd.clear();
      cursorColumn = 0;
      currentCode = "";
    }
  }

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(GREEN_LED_PIN, LOW);
  }
}