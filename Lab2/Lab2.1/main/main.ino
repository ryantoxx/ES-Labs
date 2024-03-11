#include <Arduino.h>

#include "task_1.h"
#include "task_2.h"
#include "task_3.h"
#include "task_4.h"

#include "timer-api.h"


// frequency 
#define REC_1 200
#define REC_2 200
#define REC_3 150

// delay
#define OFFSET_1 2
#define OFFSET_2 1
#define OFFSET_3 3

// counters
int recCnt_1 = OFFSET_1;
int recCnt_2 = OFFSET_2;
int recCnt_3 = OFFSET_3;


void setup() {

  // 1kHz = 1ms
  timer_init_ISR_1KHz(TIMER_DEFAULT);

  task_1_setup();
  task_2_setup();
  task_3_setup(REC_2);
  task_4_setup();

}

void loop() {

  task_4_impl();
  delay(200);

}

void timer_handle_interrupts(int timer) {

  if (--recCnt_1 <= 0) {
      task_1_impl();
      recCnt_1 = REC_1;
  }

  if (--recCnt_2 <= 0) {
      task_2_impl();
      recCnt_2 = REC;
  }

  if (--recCnt_3 <= 0) {
      task_3_impl();
      recCnt_3 = REC_3;
  }

}

