#include "l298.h"
#include <Arduino.h>

void l298_init(void) {
  pinMode(IN1_PIN, OUTPUT);
  pinMode(IN2_PIN, OUTPUT);
  pinMode(ENA_PIN, OUTPUT);

}

void l298_set_ENA(int speed) {
  analogWrite(ENA_PIN, speed);
}

void l298_IN1_HIGH(void) {
  digitalWrite(IN1_PIN, HIGH);
}

void l298_IN1_LOW(void) {
  digitalWrite(IN1_PIN, LOW);
}

void l298_IN2_HIGH(void) {
  digitalWrite(IN2_PIN, HIGH);
}

void l298_IN2_LOW(void) {
  digitalWrite(IN2_PIN, LOW);
}




