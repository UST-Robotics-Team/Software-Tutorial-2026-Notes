#include "ultrasonic_gpio.h"
#include "tutorial_config.h"
#include "tim.h"

uint16_t Ultrasonic_TrigPin(void) { return ULTRASONIC_TRIG_Pin; }
uint16_t Ultrasonic_EchoPin(void) { return ULTRASONIC_ECHO_Pin; }

HAL_StatusTypeDef Ultrasonic_GPIO_Init(void)
{
    /* GPIO and TIM2 are initialized by CubeMX; start the counter once. */
    g_ultrasonic.wiring = US_WIRING_UNDETECTED;
    return HAL_TIM_Base_Start(&htim2);
}
uint32_t Ultrasonic_Micros(void) { return __HAL_TIM_GET_COUNTER(&htim2); }
void Ultrasonic_Trigger(bool high)
{
    HAL_GPIO_WritePin(ULTRASONIC_GPIO_Port, ULTRASONIC_TRIG_Pin,
                     high ? GPIO_PIN_SET : GPIO_PIN_RESET);
}
bool Ultrasonic_Echo(void)
{
    return HAL_GPIO_ReadPin(ULTRASONIC_GPIO_Port, ULTRASONIC_ECHO_Pin) == GPIO_PIN_SET;
}
