#ifndef MAINBOARD_STUDENT_TASKS_H
#define MAINBOARD_STUDENT_TASKS_H
#include "sensors.h"
/* The app calls CW2 only for a successful ADC reading; draw the label on row 2. */
void CW2_ProcessIR(const IR_Sample *sample);
/* false: task unfinished; show DO CW3 TODO and do not measure.
   true: use this task's status/result, including an error.
   Students implement sequencing and propagate failures. */
bool CW3_MeasureUltrasonic(uint32_t *distance_mm, HAL_StatusTypeDef *status);
#endif
