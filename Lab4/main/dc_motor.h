#ifndef DC_MOTOR_H
#define DC_MOTOR_H

#define MOTOR_MAX_POWER 100 

void motor_init(void);
void motor_pow_up();
void motor_pow_down();
int motor_set_pow(int motor_power);
void motor_stop(void);

#endif