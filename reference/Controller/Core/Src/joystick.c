#include "joystick.h"
#include "adc.h"
/* DMA writes halfwords. Static lifetime is required; do not use a local buffer. */
volatile uint16_t g_joystick_samples[4] __attribute__((aligned(4)));
volatile uint16_t g_joystick_observed_min[4] = {4095U,4095U,4095U,4095U};
volatile uint16_t g_joystick_observed_max[4];
HAL_StatusTypeDef Joystick_Start(void)
{
    HAL_StatusTypeDef status = HAL_ADCEx_Calibration_Start(&hadc1);
    if (status != HAL_OK) return status;
    status = HAL_ADC_Start_DMA(&hadc1, (uint32_t *)(uintptr_t)g_joystick_samples, 4);
    /* This lesson reads the live buffer and does not use DMA callbacks.
       Disable transfer interrupts; DMA itself continues in circular mode. */
    if (status == HAL_OK)
        __HAL_DMA_DISABLE_IT(hadc1.DMA_Handle, DMA_IT_HT | DMA_IT_TC | DMA_IT_TE);
    return status;
}
void Joystick_Read(uint16_t values[4])
{
    /* Each channel is an independent latest sample, not an atomic four-axis frame. */
    for (unsigned i = 0; i < 4; ++i) {
        uint16_t value = g_joystick_samples[i];
        values[i] = value;
        if (value < g_joystick_observed_min[i]) g_joystick_observed_min[i] = value;
        if (value > g_joystick_observed_max[i]) g_joystick_observed_max[i] = value;
    }
}
