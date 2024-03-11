#include <Arduino.h>
#include "task_3.h"
#include "task_2.h"

void task_3_setup(int REC, int OFFSET) {

  pinMode(BUTTON2_PIN, OUTPUT);
  pinMode(BUTTON3_PIN, OUTPUT);

  REC3 = REC;
  OFFSET3 = OFFSET;
}

void task_3_impl(void *pvParameters) {
  (void) pvParameters;

  TickType_t xLastWakeTime;
  const TickType_t xFrequency = pdMS_TO_TICKS(REC3);
  BaseType_t xWasDelayed;

  vTaskDelay(OFFSET3 / portTICK_PERIOD_MS);
  xLastWakeTime = xTaskGetTickCount();

  for (;;) {
    xWasDelayed = xTaskDelayUntil(&xLastWakeTime, xFrequency);

    if (digitalRead(BUTTON2_PIN) == HIGH && REC2 < MAX_INTERVAL) {
      REC2 += 100;
    } else if (digitalRead(BUTTON3_PIN) == HIGH && REC2 > MIN_INTERVAL) {
      REC2 -= 100;
    }
  }
}
