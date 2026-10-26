#ifndef TUTORIAL_JOYSTICK_H
#define TUTORIAL_JOYSTICK_H
#include "main.h"
extern volatile uint16_t g_joystick_samples[4];
extern volatile uint16_t g_joystick_observed_min[4], g_joystick_observed_max[4];
HAL_StatusTypeDef Joystick_Start(void);
void Joystick_Read(uint16_t values[4]);
#endif
