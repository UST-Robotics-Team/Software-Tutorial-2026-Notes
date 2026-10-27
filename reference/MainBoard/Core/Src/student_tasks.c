#include "student_tasks.h"
#include "tutorial_config.h"
#include "ultrasonic_gpio.h"
#include "lcd/lcd.h"

void CW2_ProcessIR(const IR_Sample *sample)
{
    bool black = IR_BLACK_IS_HIGH ? sample->raw >= IR_THRESHOLD
                                 : sample->raw < IR_THRESHOLD;
    tft_prints(0, 2, black ? "SURFACE: BLACK" : "SURFACE: WHITE");
}

bool CW3_MeasureUltrasonic(uint32_t *distance_mm, HAL_StatusTypeDef *status)
{
    *distance_mm = 0U;
    *status = Ultrasonic_Begin();
    if (*status != HAL_OK) return true;
    Ultrasonic_Trigger(true);
    Ultrasonic_DelayUs(ULTRASONIC_TRIGGER_US);
    Ultrasonic_Trigger(false);
    uint32_t transaction_start = Ultrasonic_Micros();
    uint32_t rise_us = 0U, fall_us = 0U;
    *status = Ultrasonic_WaitEdges(transaction_start, &rise_us, &fall_us);
    if (*status != HAL_OK) return true;
    uint32_t width_us = fall_us - rise_us;
    uint32_t measured_mm = (width_us * ULTRASONIC_MM_NUMERATOR
                          + ULTRASONIC_MM_DENOMINATOR / 2U)
                          / ULTRASONIC_MM_DENOMINATOR;
    *status = Ultrasonic_Complete(width_us, measured_mm, distance_mm);
    return true;
}
