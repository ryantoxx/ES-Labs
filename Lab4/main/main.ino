#include <Arduino.h>
#include <LiquidCrystal.h>
#include <stdio.h>
#include <string.h>

#include "lamp.h"
#include "dc_motor.h"

#define BAUD_RATE 9600
#define LCD_WIDTH 16
#define LCD_LENGTH 2

const int RS = A5, EN = A4, D4 = A3, D5 = A2, D6 = A1, D7 = A0;
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

int my_putChar(char ch, FILE * f) {
  return Serial.write(ch);
}
char my_getChar(FILE * f) {
  while(!Serial.available()) {
  }
  return Serial.read();
}

void setup() {
  Serial.begin(BAUD_RATE);
  FILE *my_stream = fdevopen(my_putChar, my_getChar);
  stdin = stdout = my_stream;

  lcd.begin(LCD_WIDTH, LCD_LENGTH);
  lamp_init();  
  motor_init();  
}

char cmd[64] = ""; 

void loop() {
  // if (Serial.available()) {
  //   char incomingByte;
  //   scanf("%c", &incomingByte);

  //   if (incomingByte == ' ') { 
  //     processCommand();
  //   } else {
  //     strncat(commandString, &incomingByte, 1);
  //   }
  // }
  scanf("%s", cmd);
  execute();
}

void execute() {
  if (strcmp(cmd, "on") == 0) {
    lamp_on();
    lcd.setCursor(0, 0);
    lcd.print("Relay:TURNED ON ");
  } else if (strcmp(cmd, "off") == 0) {
    lamp_off();
    lcd.setCursor(0, 0);
    lcd.print("Relay:TURNED OFF     ");
  } else if (atoi(cmd) >= -100 && atoi(cmd) <= 100) {
    int command = atoi(cmd);

    motor_set_pow(command);
    if (command > 0) {
      motor_pow_up();
      lcd.setCursor(0, 0);
      lcd.print("Motor: " + String(command) + "      ");
    } else if (command < 0) {
      motor_pow_down();
      lcd.setCursor(0, 0);
      lcd.print("Motor: " + String(command) + "      ");
    }
  } else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("No command");
  }

  memset(cmd, 0, sizeof(cmd));
}

