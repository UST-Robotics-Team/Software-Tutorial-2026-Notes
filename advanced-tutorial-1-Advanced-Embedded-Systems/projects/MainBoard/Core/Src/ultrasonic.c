/* CW3 timing tasks and supplied diagnostic/output helpers. */
#include "ultrasonic_gpio.h"
#include "tutorial_config.h"
volatile Ultrasonic_Diagnostics g_ultrasonic;

HAL_StatusTypeDef Ultrasonic_DelayUs(uint32_t duration)
{
    /* TODO CW3A: delay using unsigned timer differences, in microseconds.
       Also use a finite HAL_GetTick deadline if the timer stops advancing. */
    (void)duration;
    return HAL_ERROR;
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
    HAL_StatusTypeDef status = Ultrasonic_DelayUs(ULTRASONIC_SETTLE_US);
    if (status != HAL_OK) g_ultrasonic.reason = US_TIMER_ERROR;
    return status;
}

HAL_StatusTypeDef Ultrasonic_WaitEdges(uint32_t transaction_start,
                                      uint32_t *rise, uint32_t *fall)
{
    /* TODO CW3B: capture rising/falling edges with one shared 250 ms deadline.
       Check the deadline before accepting either edge, including at the limit.
       Use a bounded millisecond watchdog too if the microsecond clock stalls.
       Set US_NO_RISE or US_NO_FALL on the matching timeout. */
    (void)transaction_start;
    (void)rise;
    (void)fall;
    g_ultrasonic.reason = US_EDGE_TASK;
    return HAL_ERROR;
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
