#ifndef TUTORIAL_SENSORS_H
#define TUTORIAL_SENSORS_H
#include "main.h"
#include <stdbool.h>
typedef struct { uint16_t raw; uint8_t d0; } IR_Sample;
typedef struct { uint16_t distance_mm; uint8_t range_status; bool valid; } TOF_Sample;
HAL_StatusTypeDef IR_Read(IR_Sample *sample);
HAL_StatusTypeDef TOF_Init(void);
HAL_StatusTypeDef TOF_Read(TOF_Sample *sample);
#endif
