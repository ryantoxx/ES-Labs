#ifndef TASK_2_H
#define TASK_2_H

#define LED2_PIN 12

int LED2_STATE;
int REC2;
int OFFSET2;

void task_2_setup(int REC, int OFFSET);
void task_2_impl(void *pvParameters);

#endif