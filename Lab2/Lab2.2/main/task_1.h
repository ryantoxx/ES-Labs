#ifndef TASK_1_H
#define TASK_1_H

#define LED1_PIN 13
#define BUTTON1_PIN 4

int BUTTON1_STATE = 0;
extern int LED1_STATE = LOW;

int OFFSET1;
int REC1;

void task_1_setup(int REC, int OFFSET);
void task_1_impl(void *pvParameters);

#endif