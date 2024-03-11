#ifndef TASK_3_H
#define TASK_3_H

#define BUTTON2_PIN 3
#define BUTTON3_PIN 2

int REC;

int MAX_INTERVAL = 3000;
int MIN_INTERVAL = 100;

void task_3_setup(int REC2);
void task_3_impl();

#endif