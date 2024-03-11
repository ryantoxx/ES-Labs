#ifndef TASK_4_H
#define TASK_4_H

#include "task_3.h"

#define BAUD_RATE 9600

int CNT_REC = 0;
int LAST_LED_STATE = HIGH;

void task_4_setup();
void task_4_impl();

#endif