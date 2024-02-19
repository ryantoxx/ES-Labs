#include <Keypad.h>
#include <LiquidCrystal.h>

#define RED_PIN 13
#define GREEN_PIN 12

#define LCD_WIDTH 16
#define LCD_LENGTH 2

#define INTERVAL 1000
#define MESSAGE_DISPLAY_TIME 1000

#define CORRECT_CODE "CORRECT"
#define WRONG_CODE "WRONG"

const int ROW_NUM    = 4; 
const int COLUMN_NUM = 4; 
unsigned long previousMillis = 0;
unsigned long messageDisplayStart = 0;

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

void setup(){
  lcd.begin(LCD_WIDTH, LCD_LENGTH);

  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
}

void loop(){
  char key = keypad.getKey();

  if (key) {
    lcd.setCursor(cursorColumn, cursorRow); 
    lcd.print(key);                
    currentCode += key;

    cursorColumn++;

    int codeLength = 4;             

    if (cursorColumn == codeLength) {
      int ledPin;
      bool correctCode = false;

      if (currentCode == validCode) {
        ledPin = GREEN_PIN;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(CORRECT_CODE);
        correctCode = true;
      } else {
        ledPin = RED_PIN;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(WRONG_CODE);
        correctCode = true;
      }

      digitalWrite(ledPin, HIGH);
      messageDisplayStart = millis();

      cursorColumn = 0;
      currentCode = "";

      if (correctCode) {
        previousMillis = millis(); 
      }
    }
  }

  unsigned long currentMillis = millis();

  if ((currentMillis - messageDisplayStart >= MESSAGE_DISPLAY_TIME) && (cursorColumn == 0)) {
    digitalWrite(RED_PIN, LOW);
    digitalWrite(GREEN_PIN, LOW);
    lcd.clear(); 
  }

  if (currentMillis - previousMillis >= INTERVAL) {
    digitalWrite(RED_PIN, LOW);
    digitalWrite(GREEN_PIN, LOW);
    previousMillis = currentMillis;
  }
}

