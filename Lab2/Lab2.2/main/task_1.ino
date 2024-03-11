#include <Arduino.h>
#include "task_1.h"

void task_1_setup(int REC, int OFFSET) {
  pinMode(LED1_PIN, OUTPUT);
  pinMode(BUTTON1_PIN, INPUT);

  REC1 = REC;
  OFFSET1 = OFFSET;
}

void task_1_impl(void *pvParameters) {
  (void) pvParameters;

  TickType_t xLastWakeTime;
  const TickType_t xFrequency = pdMS_TO_TICKS(REC1);
  BaseType_t xWasDelayed;

  vTaskDelay(OFFSET1 / portTICK_PERIOD_MS);
  xLastWakeTime = xTaskGetTickCount();

  for (;;) {

    BUTTON1_STATE = digitalRead(BUTTON1_PIN);
    
    xWasDelayed = xTaskDelayUntil(&xLastWakeTime, xFrequency);
    if (BUTTON1_STATE == HIGH) {
      LED1_STATE = digitalRead(LED1_PIN);
      LED1_STATE = !LED1_STATE;
      digitalWrite(LED1_PIN, LED1_STATE);
    } 
  }
}
