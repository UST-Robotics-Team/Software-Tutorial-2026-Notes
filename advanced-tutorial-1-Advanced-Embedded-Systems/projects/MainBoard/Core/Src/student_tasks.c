#include "student_tasks.h"
#include "tutorial_config.h"
#include "ultrasonic_gpio.h"
#include "lcd/lcd.h"

void CW2_ProcessIR(const IR_Sample *sample)
{
    /* TODO CW2C: classify successful A0 samples using your measured threshold
       and polarity. Draw the label on row 2; compare it with the separate D0. */
    (void)sample;
    tft_prints(0, 2, "SURFACE: ?");
}

bool CW3_MeasureUltrasonic(uint32_t *distance_mm, HAL_StatusTypeDef *status)
{
    /* TODO CW3A/B/C: assemble one complete transaction using your timer/GPIO
       functions. Keep Trig LOW during the response and on every exit path.
       Use the supplied Begin/Complete guards, capture both edges, subtract
       unsigned timestamps and derive the round-trip conversion to mm.
       Return false while unfinished; otherwise return true with a HAL status.
       On failure, do not publish a distance from a previous attempt. */
    (void)distance_mm;
    (void)status;
    return false;
}
