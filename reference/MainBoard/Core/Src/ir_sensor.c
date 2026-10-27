#include "sensors.h"
#include "adc.h"
#include "tutorial_config.h"
HAL_StatusTypeDef IR_Read(IR_Sample *sample)
{
    if (!sample) return HAL_ERROR;
    sample->raw = 0;
    sample->d0 = 0;
    HAL_StatusTypeDef status = HAL_ADC_Start(&hadc1);
    if (status != HAL_OK) return status;
    status = HAL_ADC_PollForConversion(&hadc1, SENSOR_IO_TIMEOUT_MS);
    if (status == HAL_OK) {
        sample->raw = (uint16_t)HAL_ADC_GetValue(&hadc1);
        sample->d0 = HAL_GPIO_ReadPin(IR_D0_GPIO_Port, IR_D0_Pin) == GPIO_PIN_SET;
    }
    HAL_StatusTypeDef stopped = HAL_ADC_Stop(&hadc1);
    return status == HAL_OK ? stopped : status;
}
