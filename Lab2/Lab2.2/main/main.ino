#include <Arduino.h>
#include <Arduino_FreeRTOS.h>

#include "task_1.h"
#include "task_2.h"
#include "task_3.h"
#include "task_4.h"

// frequency 
#define REC_1 200
#define REC_2 200
#define REC_3 200
#define REC_4 100

// delay
#define OFFSET_1 1
#define OFFSET_2 1
#define OFFSET_3 3
#define OFFSET_4 1

// counters
int recCnt_1 = OFFSET_1;
int recCnt_2 = OFFSET_2;
int recCnt_3 = OFFSET_3;
int recCnt_4 = OFFSET_4;

void setup() {

  task_1_setup(REC_1, recCnt_1);
  task_2_setup(REC_2, recCnt_2);
  task_3_setup(REC_3, recCnt_3);
  task_4_setup(REC_4, recCnt_4);

  xTaskCreate(
    task_1_impl
    ,  "ON/OFF LED" // name
    ,  128  // stack size
    ,  NULL
    ,  3  // Priority, (0 - 3)
    ,  NULL );

    xTaskCreate(
    task_2_impl
    ,  "Blinking LED"
    ,  128
    ,  NULL
    ,  2
    ,  NULL );

    xTaskCreate(
    task_3_impl
    ,  "INC/DEC Buttons"
    ,  128  
    ,  NULL
    ,  2
    ,  NULL );

    xTaskCreate(
    task_4_impl
    ,  "Idle Task"   
    ,  128
    ,  NULL
    ,  0
    ,  NULL );
}

void loop() {
  // empty
}


