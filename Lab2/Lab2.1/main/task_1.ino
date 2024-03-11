#include <Arduino.h>
#include "task_1.h"

void task_1_setup() {
  pinMode(LED1_PIN, OUTPUT);     
  pinMode(BUTTON1_PIN, INPUT);   
}

void task_1_impl() {

  BUTTON1_STATE = digitalRead(BUTTON1_PIN);  
  
  if (BUTTON1_STATE == HIGH) {
    digitalWrite(LED1_PIN, HIGH);  
  } else {
    digitalWrite(LED1_PIN, LOW);   
  }
}