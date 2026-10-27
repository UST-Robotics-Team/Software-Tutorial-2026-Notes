#include "ultrasonic_gpio.h"
#include "tutorial_config.h"
/* Add tim.h after configuring TIM2 and generating code in CW3A. */

uint16_t Ultrasonic_TrigPin(void) { return ULTRASONIC_TRIG_Pin; }
uint16_t Ultrasonic_EchoPin(void) { return ULTRASONIC_ECHO_Pin; }

HAL_StatusTypeDef Ultrasonic_Start(void)
{
    /* TODO CW3A: start the generated TIM2 base once and report its HAL status.
       Do not initialize GPIO, clocks or timer registers here. */
    return HAL_ERROR;
}
uint32_t Ultrasonic_Micros(void)
{
    /* TODO CW3A: read the generated timer's counter through the HAL macro. */
    return 0U;
}
void Ultrasonic_Trigger(bool high)
{
    /* TODO CW3A: drive PA0 HIGH or LOW with HAL GPIO. */
    (void)high;
}
bool Ultrasonic_Echo(void)
{
    /* TODO CW3B: read PA1 as a digital level. */
    return false;
}
