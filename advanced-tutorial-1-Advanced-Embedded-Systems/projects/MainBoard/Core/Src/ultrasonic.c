/* Supplied bounded helpers for CW3.
   Students write the trigger, pulse width and distance calculation.
   TIM2 supplies microseconds; unsigned subtraction handles counter wrap. */
#include "ultrasonic_gpio.h"
#include "tutorial_config.h"
volatile Ultrasonic_Diagnostics g_ultrasonic;

void Ultrasonic_DelayUs(uint32_t duration)
{
    uint32_t start = Ultrasonic_Micros();
    while ((uint32_t)(Ultrasonic_Micros() - start) < duration) {}
}

HAL_StatusTypeDef Ultrasonic_Begin(void)
{
    ++g_ultrasonic.attempts;
    g_ultrasonic.pulse_us = 0U;
    g_ultrasonic.distance_mm = 0U;
    g_ultrasonic.reason = US_OK;
    g_ultrasonic.echo_idle = Ultrasonic_Echo();
    Ultrasonic_Trigger(false);
    if (g_ultrasonic.echo_idle) {
        g_ultrasonic.reason = US_ECHO_BUSY;
        return HAL_BUSY;
    }
    Ultrasonic_DelayUs(ULTRASONIC_SETTLE_US);
    return HAL_OK;
}

static bool WaitEcho(bool high, uint32_t transaction_start, uint32_t *edge)
{
    for (;;) {
        bool level = Ultrasonic_Echo();
        uint32_t now = Ultrasonic_Micros();
        if ((uint32_t)(now - transaction_start) >= ULTRASONIC_TIMEOUT_US) return false;
        if (level == high) { *edge = now; return true; }
    }
}

HAL_StatusTypeDef Ultrasonic_WaitEdges(uint32_t transaction_start,
                                      uint32_t *rise, uint32_t *fall)
{
    /* Trig must be LOW throughout the response. Both edges share a deadline. */
    Ultrasonic_Trigger(false);
    if (!rise || !fall) {
        g_ultrasonic.reason = US_BAD_RESULT;
        return HAL_ERROR;
    }
    *rise = *fall = 0U;
    if (!WaitEcho(true, transaction_start, rise)) {
        g_ultrasonic.reason = US_NO_RISE;
        return HAL_TIMEOUT;
    }
    if (!WaitEcho(false, transaction_start, fall)) {
        g_ultrasonic.reason = US_NO_FALL;
        return HAL_TIMEOUT;
    }
    return HAL_OK;
}

HAL_StatusTypeDef Ultrasonic_Complete(uint32_t width_us, uint32_t measured_mm,
                                     uint32_t *distance_mm)
{
    Ultrasonic_Trigger(false);
    g_ultrasonic.distance_mm = 0U;
    if (!distance_mm) { g_ultrasonic.reason = US_BAD_RESULT; return HAL_ERROR; }
    *distance_mm = 0U;
    g_ultrasonic.pulse_us = width_us;
    if (width_us < ULTRASONIC_MIN_PULSE_US) {
        g_ultrasonic.reason = US_TOO_SHORT;
        return HAL_ERROR;
    }
    if (width_us >= ULTRASONIC_TIMEOUT_US || measured_mm == 0U ||
        measured_mm > ULTRASONIC_TIMEOUT_US * ULTRASONIC_MM_NUMERATOR /
                      ULTRASONIC_MM_DENOMINATOR) {
        g_ultrasonic.reason = US_BAD_RESULT;
        return HAL_ERROR;
    }
    /* Do not replace a student's plausible but incorrect conversion with the
       reference answer. The ruler comparison is part of the exercise. */
    *distance_mm = measured_mm;
    g_ultrasonic.distance_mm = measured_mm;
    g_ultrasonic.reason = US_OK;
    ++g_ultrasonic.successes;
    g_ultrasonic.wiring = US_WIRING_BOARD;
    return HAL_OK;
}
