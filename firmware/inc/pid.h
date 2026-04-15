#ifndef PID_H
#define PID_H

#include <stdint.h>

typedef struct {
    float Kp, Ki, Kd;
    float dt;
    float integral;
    float prev_error;
    float output_min, output_max;
    float integral_min, integral_max;
} PID_HandleTypeDef;

void PID_Init(PID_HandleTypeDef *pid, float Kp, float Ki, float Kd, float dt);
void PID_SetOutputLimits(PID_HandleTypeDef *pid, float min, float max);
void PID_SetIntegralLimits(PID_HandleTypeDef *pid, float min, float max);
float PID_Update(PID_HandleTypeDef *pid, float target, float actual);
void PID_Reset(PID_HandleTypeDef *pid);

#endif
