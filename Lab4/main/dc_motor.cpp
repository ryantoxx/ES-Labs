#include "dc_motor.h"
#include "l298.h"
#include <Arduino.h>

void motor_init(void) {
  l298_init();
}

void motor_pow_up() {
  l298_IN1_HIGH();
  l298_IN2_LOW();
}

void motor_pow_down() {
  l298_IN1_LOW();
  l298_IN2_HIGH();
}


int motor_set_pow(int motor_power) {
  int speed = map(abs(motor_power), 0, 100, 0, 255);
  l298_set_ENA(speed);
}

void motor_stop(void) {
  l298_IN1_LOW();
  l298_IN2_LOW();
}