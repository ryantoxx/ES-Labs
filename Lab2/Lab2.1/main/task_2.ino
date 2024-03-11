#include <Arduino.h>
#include "task_1.h"
#include "task_2.h"

void task_2_setup() {

  pinMode(LED2_PIN, OUTPUT);
}

void task_2_impl() {

  LED1_STATE = digitalRead(LED1_PIN);
  if (LED1_STATE == LOW)

    LED2_STATE = digitalRead(LED2_PIN);
  if (LED2_STATE == LOW) {
    digitalWrite(LED2_PIN, HIGH);
  } else {
    digitalWrite(LED2_PIN, LOW);
  }

  return 0;
}
