#include <Arduino.h>
#include <LiquidCrystal.h>

#define BAUD_RATE 9600
#define LCD_WIDTH 16
#define LCD_LENGTH 4
#define PWM_MIN 0
#define PWM_MAX 255
#define TEMP_PIN A0
#define LED_PIN 10
#define RELAY_PIN 9
#define MIN_VALUE 0
#define MAX_VALUE 100

// Temperature data
const float TempVoltageOffset = 0.5;
const int TempIndex = 100;
const float SystemReferenceVoltage = 5.0;  // ADC reference voltage
const float SystempResolution = 1023.0;    // ADC resolution for 10 bits
const int histerezis = 2;

const int RS = 7, EN = 6, D4 = 5, D5 = 4, D6 = 3, D7 = 2;
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

int tempSetPoint = 25;  // default temperature set point
int ledSetPoint = 50;   // default LED set point


int my_putChar(char ch, FILE *f) {
  return Serial.write(ch);
}
char my_getChar(FILE *f) {
  while (!Serial.available()) {
  }
  return Serial.read();
}

char inputBuffer[5] = "";
char cmd[5] = "";

void setup() {
  Serial.begin(BAUD_RATE);
  lcd.begin(LCD_WIDTH, LCD_LENGTH);
  FILE *my_stream = fdevopen(my_putChar, my_getChar);
  stdin = stdout = my_stream;

  pinMode(LED_PIN, OUTPUT);
  pinMode(RELAY_PIN, OUTPUT);
}

void loop() {
  while (Serial.available() > 0) {

    scanf("%s %s", cmd, inputBuffer);
    if (strcmp(cmd, "led") == 0) {
      ledSetPoint = atoi(inputBuffer);
    } else if (strcmp(cmd, "temp") == 0) {
      tempSetPoint = atoi(inputBuffer);
    }
  }

  float temperature = readTempSensor();
  int brightness = controlLED();
  controlRelay(temperature);
  updateLCD(temperature, brightness);

  delay(500);
}

float readTempSensor() {
  int TempSensorValue = analogRead(TEMP_PIN);

  // ADC value to voltage
  float TempVoltage = (TempSensorValue / SystempResolution) * SystemReferenceVoltage;

  // voltage to temperature
  float temperature = (TempVoltage - TempVoltageOffset) * TempIndex;

  return temperature;
}

int controlLED() {
  int brightness = map(ledSetPoint, MIN_VALUE, MAX_VALUE, PWM_MIN, PWM_MAX);
  analogWrite(LED_PIN, brightness);
  return brightness;
}

void controlRelay(float temperature) {
  if (temperature > tempSetPoint + histerezis) {
    digitalWrite(RELAY_PIN, LOW);
  } else if (temperature < tempSetPoint - histerezis) {
    digitalWrite(RELAY_PIN, HIGH);
  }
}

void updateLCD(float temperature, int brightness) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Relay State: ");
  if (digitalRead(RELAY_PIN) == HIGH) {
    lcd.print("ON");
  } else {
    lcd.print("OFF");
  }
  lcd.setCursor(0, 1);
  lcd.print("Temp Set: ");
  lcd.print(tempSetPoint);
  lcd.print(" C  ");
  lcd.setCursor(0, 2);
  lcd.print("Brightness: ");
  lcd.print(brightness);
  lcd.setCursor(0, 3);
  lcd.print("LED Set: ");
  lcd.print(ledSetPoint);
  lcd.print("%");
}
