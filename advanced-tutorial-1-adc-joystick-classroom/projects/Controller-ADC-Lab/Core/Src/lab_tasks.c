#include "lab_tasks.h"
#include "adc.h"

bool LabStudent_PrepareADC(HAL_StatusTypeDef *status)
{
    /* A: perform the F103 ADC preparation once at startup. */
    (void)status;
    return false;
}

bool LabStudent_ReadPolling(uint16_t *raw, HAL_StatusTypeDef *status)
{
    /* A: acquire one completed conversion, with bounded waiting and errors. */
    (void)raw; (void)status;
    return false;
}

bool LabStudent_ToMillivolts(uint16_t raw, uint16_t reference_mv,
                           uint32_t *millivolts)
{
    /* A: endpoint-scaled estimate: zero -> 0 mV, largest code -> reference_mv.
       Intermediate values must work too; this is not an ADC accuracy model. */
    (void)raw; (void)reference_mv; (void)millivolts;
    return false;
}

bool LabStudent_StartDMA(volatile uint16_t samples[LAB_AXIS_COUNT],
                         HAL_StatusTypeDef *status)
{
    /* B: start acquisition into this persistent buffer once. Length is four
       transfers, with the transfer width selected in the IOC. */
    (void)samples; (void)status;
    return false;
}

bool LabStudent_NormalizeAxis(uint16_t raw, uint16_t minimum, uint16_t centre,
                             uint16_t maximum, uint16_t deadband, float *value)
{
    /* C: produce a continuous signed position in [-1, 1], with a centre deadband.
       Treat invalid calibration as zero. Use the supplied parameters. */
    (void)raw; (void)minimum; (void)centre; (void)maximum;
    (void)deadband; (void)value;
    return false;
}

bool LabStudent_StickExtent(float x, float y, float *extent)
{
    /* Extension: a direction-independent displacement in [0, 1]. */
    (void)x; (void)y; (void)extent;
    return false;
}
