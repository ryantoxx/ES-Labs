#include <Arduino.h>
#include "task_1.h"
#include "task_2.h"

void task_2_setup(int REC, int OFFSET) {
  pinMode(LED2_PIN, OUTPUT);

  REC2 = REC;
  OFFSET2 = OFFSET;
}

void task_2_impl(void *pvParameters) {
  (void)pvParameters;

  TickType_t xLastWakeTime;
  TickType_t xFrequency = pdMS_TO_TICKS(REC2);
  BaseType_t xWasDelayed;

  vTaskDelay(OFFSET2 / portTICK_PERIOD_MS);
  xLastWakeTime = xTaskGetTickCount();

  for (;;) {
    xFrequency = pdMS_TO_TICKS(REC2);

    if (LED1_STATE == LOW) {
      //xWasDelayed = xTaskDelayUntil(&xLastWakeTime, xFrequency);
      digitalWrite(LED2_PIN, HIGH);           // turn the LED on (HIGH is the voltage level)
      xWasDelayed = xTaskDelayUntil(&xLastWakeTime, xFrequency);
      //vTaskDelay(REC2 / portTICK_PERIOD_MS);
      digitalWrite(LED2_PIN, LOW);            // turn the LED off by making the voltage LOW
      xWasDelayed = xTaskDelayUntil(&xLastWakeTime, xFrequency);
      //vTaskDelay(REC2 / portTICK_PERIOD_MS);
    }
  }
}
