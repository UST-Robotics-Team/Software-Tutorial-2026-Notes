#include "sensors.h"
#include "tutorial_config.h"
/* Add adc.h after enabling ADC1 IN3 and generating code in CW2B. */

HAL_StatusTypeDef IR_ReadDigital(uint8_t *d0)
{
    /* TODO CW2A: read PA2 with HAL GPIO, write 0 or 1, and report success.
       Keep the output unchanged on failure. */
    (void)d0;
    return HAL_ERROR;
}

HAL_StatusTypeDef IR_Read(IR_Sample *sample)
{
    /* TODO CW2B: obtain A0 by single-conversion polling and D0 using your
       digital function. Check statuses, use a finite timeout and stop the ADC.
       Publish the sample only when the complete operation succeeds.
       F405 does not use the F103 ADC self-calibration call. */
    (void)sample;
    return HAL_ERROR;
}
