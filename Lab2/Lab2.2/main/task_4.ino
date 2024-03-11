#include "task_4.h"

void task_4_setup(int REC, int OFFSET) {
  Serial.begin(BAUD_RATE);

  REC4 = REC;
  OFFSET4 = OFFSET;
}

void task_4_impl(void *pvParameters) {
  (void) pvParameters;

  TickType_t xLastWakeTime;
  const TickType_t xFrequency = pdMS_TO_TICKS(REC4);
  BaseType_t xWasDelayed;

  vTaskDelay(OFFSET4 / portTICK_PERIOD_MS);
  xLastWakeTime = xTaskGetTickCount();

  
  for (;;) {
    // xWasDelayed = xTaskDelayUntil(&xLastWakeTime, xFrequency);

    if (LED1_STATE != LAST_LED_STATE) {
      if (LED1_STATE == HIGH) {
        Serial.println("Led 1 has turned on.");
        Serial.println("Led 2 has stopped.");
      } else {
        Serial.println("Led 1 has turned off");
        Serial.println("Led 2 has started blinking");
      }
      LAST_LED_STATE = LED1_STATE;
    }

    if (REC2 != CNT_REC) {
      Serial.println("TASK2 recurrence has been set to " + String(REC2) + " ms.");
      CNT_REC = REC2;

      if (REC2 >= MAX_INTERVAL) {
        Serial.println("The recurrence has reached it's maximum value.");
      } else if (REC2 <= MIN_INTERVAL) {
        Serial.println("The recurrence has reached it's minimal value.");
      }
    }
  }
}
