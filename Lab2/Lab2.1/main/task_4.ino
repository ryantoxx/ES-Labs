#include "task_4.h"

void task_4_setup() {
  Serial.begin(BAUD_RATE);
}

void task_4_impl() {
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

  if (REC != CNT_REC) {
    Serial.println("TASK2 recurrence has been set to " + String(REC) + " ms.");
    CNT_REC = REC;

    if (REC >= MAX_INTERVAL) {
      Serial.println("The recurrence has reached it's maximum value.");
    } else if (REC <= MIN_INTERVAL) {
      Serial.println("The recurrence has reached it's minimal value.");
    }
  }
}
