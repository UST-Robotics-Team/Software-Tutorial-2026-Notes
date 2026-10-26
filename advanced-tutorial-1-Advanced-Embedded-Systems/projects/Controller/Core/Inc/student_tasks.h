#ifndef CONTROLLER_STUDENT_TASKS_H
#define CONTROLLER_STUDENT_TASKS_H
#include <stdbool.h>
#include <stdint.h>
bool CW1_ReadJoystick(uint16_t values[4]);
/* Continuous signed axis position before the physical direction multiplier. */
float CW1_NormalizeAxis(uint16_t raw, uint16_t minimum, uint16_t centre,
                       uint16_t maximum, uint16_t deadband);
#endif
