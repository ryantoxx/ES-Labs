#ifndef TASK_3_H
#define TASK_3_H

#define BUTTON2_PIN 3
#define BUTTON3_PIN 2

int REC3;
int OFFSET3;

int MAX_INTERVAL = 3000;
int MIN_INTERVAL = 100;

void task_3_setup(int REC, int OFFSET);
void task_3_impl(void *pvParameters);

#endif