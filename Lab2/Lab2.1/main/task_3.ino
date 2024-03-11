#include <Arduino.h>
#include "task_3.h"

void task_3_setup(int REC2) {

  pinMode(BUTTON2_PIN, OUTPUT);
  pinMode(BUTTON3_PIN, OUTPUT);

  REC = REC2;
}

void task_3_impl() {

  if(digitalRead(BUTTON2_PIN) == HIGH && REC < MAX_INTERVAL) {
    REC += 100;
  }
  else if (digitalRead(BUTTON3_PIN) == HIGH && REC > MIN_INTERVAL) {
    REC -= 100;
  }
  
}
