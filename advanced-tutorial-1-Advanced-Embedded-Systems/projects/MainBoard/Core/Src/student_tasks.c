#include "student_tasks.h"
#include "tutorial_config.h"
#include "ultrasonic_gpio.h"
#include "lcd/lcd.h"

void CW2_ProcessIR(const IR_Sample *sample)
{
    /* TODO CW2: collect A0 samples on black and white at a fixed height.
       Set IR_THRESHOLD in the gap and IR_BLACK_IS_HIGH from your observations.
       Replace the label below with an if/else using sample->raw (not D0).
       High-black: raw >= threshold. Low-black: raw < threshold.
       Compare your software label with the separately displayed sample->d0. */
    (void)sample;
    tft_prints(0, 2, "SURFACE: ?");
}

bool CW3_MeasureUltrasonic(uint32_t *distance_mm, HAL_StatusTypeDef *status)
{
    /* Remove this early return only after completing TODO A/B/C below.
       Until then the app shows DO CW3 TODO without measuring ultrasonic range.
       After removal it uses your result or shows the measurement error. */
    return false;

    /* Supplied setup and error guards: keep these lines. */
    *distance_mm = 0U;
    *status = Ultrasonic_Begin();
    if (*status != HAL_OK) return true;

    /* TODO A: drive Trig HIGH, wait ULTRASONIC_TRIGGER_US, then drive it LOW.
       Use Ultrasonic_Trigger() and Ultrasonic_DelayUs(); not HAL_Delay(). */

    uint32_t transaction_start = Ultrasonic_Micros();
    uint32_t rise_us = 0U, fall_us = 0U;
    *status = Ultrasonic_WaitEdges(transaction_start, &rise_us, &fall_us);
    if (*status != HAL_OK) return true;

    /* TODO B: replace 0U with unsigned fall_us - rise_us. */
    uint32_t width_us = 0U;
    /* TODO C: replace 0U with the rounded round-trip conversion to mm.
       Use ULTRASONIC_MM_NUMERATOR and ULTRASONIC_MM_DENOMINATOR. */
    uint32_t measured_mm = 0U;

    /* Supplied validation, diagnostics and output handling. */
    *status = Ultrasonic_Complete(width_us, measured_mm, distance_mm);
    return true;
}
