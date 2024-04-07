#ifndef L298_H
#define L298_H

#define IN1_PIN 10
#define IN2_PIN 9
#define ENA_PIN 8

void l298_init(void);
void l298_set_ENA(int speed);
void l298_IN1_HIGH(void);
void l298_IN1_LOW(void);
void l298_IN2_HIGH(void);
void l298_IN2_LOW(void);

#endif
