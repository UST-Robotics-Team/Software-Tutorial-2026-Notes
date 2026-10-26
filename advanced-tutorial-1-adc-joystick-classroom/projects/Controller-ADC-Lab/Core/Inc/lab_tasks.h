#ifndef ADC_LAB_TASKS_H
#define ADC_LAB_TASKS_H
#include "main.h"
#include "lab_config.h"
#include <stdbool.h>

/* false = unfinished task; true = implemented. For HAL operations, status
   separately reports success or failure. The application supplies valid pointers. */
bool LabStudent_PrepareADC(HAL_StatusTypeDef *status);
bool LabStudent_ReadPolling(uint16_t *raw, HAL_StatusTypeDef *status);
bool LabStudent_ToMillivolts(uint16_t raw, uint16_t reference_mv,
                           uint32_t *millivolts);
bool LabStudent_StartDMA(volatile uint16_t samples[LAB_AXIS_COUNT],
                         HAL_StatusTypeDef *status);
bool LabStudent_NormalizeAxis(uint16_t raw, uint16_t minimum, uint16_t centre,
                             uint16_t maximum, uint16_t deadband, float *value);
/* Optional extension. Inputs are signed positions, output is displacement. */
bool LabStudent_StickExtent(float x, float y, float *extent);
#endif
