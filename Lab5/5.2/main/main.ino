#include <Arduino.h>
#include <LiquidCrystal.h>
#include <PID_v1.h>
#include <Encoder.h>

#define TEMP_PIN A0
#define RELAY_PIN 2

#define IN1_PIN 7
#define IN2_PIN 6
#define ENA_PIN 5

#define ENCODER_A_PIN 3
#define ENCODER_B_PIN 4

#define BAUD_RATE 9600
#define LCD_WIDTH 40
#define LCD_LENGTH 2

const int RS = 13, EN = 12, D4 = 11, D5 = 10, D6 = 9, D7 = 8;
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

// Temperature data
const float TempVoltageOffset = 0.5;
const int TempIndex = 100;
const float SystemReferenceVoltage = 5.0;  // ADC reference voltage
const float SystempResolution = 1023.0;    // ADC resolution for 10 bits
const int histerezis = 2;

int tempSetPoint;
int motorSetPoint;
long oldPosition = -999;

volatile int encoderPos = 0;
int previousStateA;
int currentStateA;

const int ENCODER_PPR = 24;

double Kp = 25, Ki = 0.0003, Kd = 0.00001;
double Input, Output, SetPoint;
PID myPID(&Input, &Output, &SetPoint, Kp, Ki, Kd, DIRECT);

int my_putChar(char ch, FILE *f) {
  return Serial.write(ch);
}

char my_getChar(FILE *f) {
  while (!Serial.available()) {
  }
  return Serial.read();
}

int readEncoder() {
  currentStateA = digitalRead(ENCODER_A_PIN);
  if (currentStateA != previousStateA) {
    if (digitalRead(ENCODER_B_PIN) != currentStateA) {
      encoderPos++;
    } else {
      encoderPos--;
    }
  }
  previousStateA = currentStateA;

  return encoderPos;
}

void setup() {
  Serial.begin(BAUD_RATE);
  lcd.begin(LCD_WIDTH, LCD_LENGTH);
  FILE *my_stream = fdevopen(my_putChar, my_getChar);
  stdin = stdout = my_stream;

  pinMode(RELAY_PIN, OUTPUT);
  pinMode(IN1_PIN, OUTPUT);
  pinMode(IN2_PIN, OUTPUT);
  pinMode(ENA_PIN, OUTPUT);

  myPID.SetMode(AUTOMATIC);
  myPID.SetSampleTime(10); 
  myPID.SetOutputLimits(-255, 255);

  pinMode(ENCODER_A_PIN, INPUT);
  pinMode(ENCODER_B_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(ENCODER_A_PIN), readEncoder, RISING);
}

char inputBuffer[10] = "";
char cmd[10] = "";

void loop() {
  while (Serial.available() > 0) {
    scanf("%s %s", cmd, inputBuffer);
     if (strcmp(cmd, "motor") == 0) {
      motorSetPoint = atoi(inputBuffer);
      lcd.setCursor(25, 1);
      lcd.print("    Mot Set:");
      lcd.print(motorSetPoint);
      lcd.print("    ");
    } else if (strcmp(cmd, "temp") == 0) {
      tempSetPoint = atoi(inputBuffer);
      lcd.setCursor(14, 0);
      lcd.print("Temp Set:");
      lcd.print(tempSetPoint);
      lcd.print(" C ");
    }
  }
    int position = readEncoder() / ENCODER_PPR;

    lcd.setCursor(0, 1);
    lcd.print("Current:");
    lcd.print(position);
    lcd.print("    ");

  SetPoint = motorSetPoint;
  Input = position;
  myPID.Compute();                 // calculate new output
  
  lcd.setCursor(12, 1);
  lcd.print("  PWM:");
  lcd.print(int(Output));
  lcd.print("   ");      

  if (Output > 0) {                      
    forward();
    analogWrite(ENA_PIN, Output);         // Enabling motor enable pin to reach the desire angle
  } else {
    reverse();
    analogWrite(ENA_PIN, abs(Output));       
  }

  float temperature = readTempSensor();
  controlRelay(temperature);
}

void forward() {
  digitalWrite(IN1_PIN, HIGH); 
  digitalWrite(IN2_PIN, LOW);
}

void reverse() {
  digitalWrite(IN1_PIN, LOW); 
  digitalWrite(IN2_PIN, HIGH);
}

float readTempSensor() {
  int TempSensorValue = analogRead(TEMP_PIN);

  // ADC value to voltage
  float TempVoltage = (TempSensorValue / SystempResolution) * SystemReferenceVoltage;

  // voltage to temperature
  float temperature = (TempVoltage - TempVoltageOffset) * TempIndex;

  lcd.setCursor(0, 0);
  lcd.print("Temp:");
  lcd.print(temperature);
  lcd.print(" C  ");

  return temperature;
}

void controlRelay(float temperature) {
  if (temperature > tempSetPoint + histerezis) {
    digitalWrite(RELAY_PIN, LOW);
  } else if (temperature < tempSetPoint - histerezis) {
    digitalWrite(RELAY_PIN, HIGH);
  }

  lcd.setCursor(29, 0);
  lcd.print("Relay:");
  if (digitalRead(RELAY_PIN) == HIGH) {
    lcd.print("ON ");
  } else {
    lcd.print("OFF");
  }
}