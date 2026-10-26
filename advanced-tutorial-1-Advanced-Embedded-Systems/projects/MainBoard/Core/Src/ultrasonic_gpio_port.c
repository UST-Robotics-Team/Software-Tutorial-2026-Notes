#include "ultrasonic_gpio.h"
#include "tutorial_config.h"

uint16_t Ultrasonic_TrigPin(void) { return ULTRASONIC_TRIG_Pin; }
uint16_t Ultrasonic_EchoPin(void) { return ULTRASONIC_ECHO_Pin; }

void Ultrasonic_GPIO_Init(void)
{
    __HAL_RCC_GPIOA_CLK_ENABLE();
    GPIO_InitTypeDef io = {0};
    io.Pin = ULTRASONIC_ECHO_Pin;
    io.Mode = GPIO_MODE_INPUT;
    io.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(ULTRASONIC_GPIO_Port, &io);
    HAL_GPIO_WritePin(ULTRASONIC_GPIO_Port, ULTRASONIC_TRIG_Pin, GPIO_PIN_RESET);
    io.Pin = ULTRASONIC_TRIG_Pin;
    io.Mode = GPIO_MODE_OUTPUT_PP;
    io.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(ULTRASONIC_GPIO_Port, &io);
    g_ultrasonic.wiring = US_WIRING_UNDETECTED;

    uint32_t clock = HAL_RCC_GetPCLK1Freq();
    if ((RCC->CFGR & RCC_CFGR_PPRE1) != 0U) clock *= 2U;
    __HAL_RCC_TIM2_CLK_ENABLE();
    __HAL_RCC_TIM2_FORCE_RESET();
    __HAL_RCC_TIM2_RELEASE_RESET();
    TIM2->PSC = clock / 1000000U - 1U;
    TIM2->ARR = UINT32_MAX;
    TIM2->EGR = TIM_EGR_UG;
    TIM2->SR = 0U;
    TIM2->CNT = 0U;
    TIM2->CR1 = TIM_CR1_CEN;
}
uint32_t Ultrasonic_Micros(void) { return TIM2->CNT; }
void Ultrasonic_Trigger(bool high)
{
    HAL_GPIO_WritePin(ULTRASONIC_GPIO_Port, ULTRASONIC_TRIG_Pin,
                     high ? GPIO_PIN_SET : GPIO_PIN_RESET);
}
bool Ultrasonic_Echo(void)
{
    return HAL_GPIO_ReadPin(ULTRASONIC_GPIO_Port, ULTRASONIC_ECHO_Pin) == GPIO_PIN_SET;
}
