#include "tutorial_app.h"
#include "student_tasks.h"
#include "tutorial_config.h"
#include "ultrasonic_gpio.h"
#include "lcd/lcd.h"

static uint32_t last_update;
static HAL_StatusTypeDef us_start_status;
#if TOF_WIRING_CONFIRMED
static HAL_StatusTypeDef tof_init_status;
static uint32_t last_tof_retry;
#endif

void TutorialApp_Init(void)
{
    us_start_status = ULTRASONIC_WIRING_CONFIRMED ? Ultrasonic_Start() : HAL_ERROR;
#if TOF_WIRING_CONFIRMED
    tof_init_status = TOF_Init();
    last_tof_retry = HAL_GetTick();
#endif
    last_update = HAL_GetTick() - SENSOR_UPDATE_MS;
}

static const char *EchoError(void)
{
    switch (g_ultrasonic.reason) {
    case US_ECHO_BUSY: return "ECHO BUSY HIGH";
    case US_NO_RISE: return "NO ECHO RISE";
    case US_NO_FALL: return "NO ECHO FALL";
    case US_TOO_SHORT: return "SHORT PULSE";
    case US_BAD_RESULT: return "BAD CALCULATION";
    case US_TIMER_ERROR: return "TIMER NOT RUNNING";
    case US_EDGE_TASK: return "EDGE TASK TODO";
    default: return "SENSOR IO ERROR";
    }
}

static void DrawIR(void)
{
    tft_prints(0, 3, "UART2 A0:R D0:T");
    if (!IR_WIRING_CONFIRMED) {
        tft_prints(0, 1, "IR WIRING CHECK");
        tft_prints(0, 2, "SURFACE: ---");
        return;
    }
    uint8_t d0 = 0U;
    if (IR_ReadDigital(&d0) != HAL_OK || d0 > 1U) {
        tft_prints(0, 1, "IR NOT READY");
        tft_prints(0, 2, "CHECK CW2 GPIO");
        return;
    }
    IR_Sample sample = {0};
    if (IR_Read(&sample) != HAL_OK || sample.raw > 4095U || sample.d0 > 1U) {
        tft_prints(0, 1, "A0:---- D0:%u", (unsigned)d0);
        tft_prints(0, 2, "ADC TODO/ERROR");
        return;
    }
    tft_prints(0, 1, "A0:%4u D0:%u", (unsigned)sample.raw, (unsigned)sample.d0);
    CW2_ProcessIR(&sample);
}

static void DrawUltrasonic(void)
{
    if (!ULTRASONIC_WIRING_CONFIRMED) {
        tft_prints(0, 4, "ULTRASONIC");
        tft_prints(0, 5, "US WIRING CHECK");
        tft_prints(0, 6, "CM: ---");
        tft_prints(0, 7, "NEAR: ---");
        return;
    }
    if (us_start_status != HAL_OK) {
        tft_prints(0, 4, "ULTRASONIC CW3");
        tft_prints(0, 5, "US NOT READY");
        tft_prints(0, 6, "CHECK CW3 TIMER");
        tft_prints(0, 7, "NEAR: ---");
        return;
    }
    uint32_t distance_mm = 0;
    HAL_StatusTypeDef status = HAL_ERROR;
    tft_prints(0, 4, "ULTRASONIC CW3");
    if (!CW3_MeasureUltrasonic(&distance_mm, &status)) {
        tft_prints(0, 5, "DO CW3 TODO");
        tft_prints(0, 6, "DIST: -----");
        tft_prints(0, 7, "NEAR: ---");
        return;
    }
    if (status != HAL_OK || distance_mm == 0U) {
        tft_prints(0, 5, "DIST: -----");
        tft_prints(0, 6, "%s", EchoError());
        tft_prints(0, 7, "NEAR: ---");
        return;
    }
    tft_prints(0, 5, "DIST:%5u mm", (unsigned)distance_mm);
    tft_prints(0, 6, "ECHO:%6u us", (unsigned)g_ultrasonic.pulse_us);
    tft_prints(0, 7, distance_mm < OBSTACLE_NEAR_MM ? "NEAR: YES" : "NEAR: NO");
}

#if TOF_WIRING_CONFIRMED
static void DrawOptionalTOF(uint32_t now)
{
    tft_prints(0, 8, "TOF (OPTIONAL)");
    if (tof_init_status != HAL_OK) {
        if ((uint32_t)(now - last_tof_retry) >= 2000U) {
            tof_init_status = TOF_Init();
            last_tof_retry = HAL_GetTick();
        }
        if (tof_init_status != HAL_OK) {
            tft_prints(0, 9, "TOF INIT ERROR");
            return;
        }
    }
    TOF_Sample sample = {0};
    HAL_StatusTypeDef status = TOF_Read(&sample);
    if (status == HAL_OK && sample.valid) {
        tft_prints(0, 9, "TOF:%5u mm", (unsigned)sample.distance_mm);
    } else {
        tft_prints(0, 9, "TOF: --- R:%u", (unsigned)sample.range_status);
    }
    if (status != HAL_OK) {
        tof_init_status = status;
        last_tof_retry = HAL_GetTick();
    }
}
#endif

void TutorialApp_Update(void)
{
    uint32_t now = HAL_GetTick();
    if ((uint32_t)(now - last_update) < SENSOR_UPDATE_MS) return;
    last_update = now;
    /* Both sensors are read in sequence, in the same program. Echo waits are
       bounded to 250 ms; a missing echo can slow this polling screen briefly.
       A failed sensor never skips the other sensor or preserves an old result. */
    tft_prints(0, 0, "IR + ULTRASONIC");
    DrawIR();
    DrawUltrasonic();
#if TOF_WIRING_CONFIRMED
    DrawOptionalTOF(HAL_GetTick());
#else
    tft_prints(0, 8, "PA0:T PA1:E");
    tft_prints(0, 9, "RUN %u s", (unsigned)(HAL_GetTick() / 1000U));
#endif
    /* The TFT clears its next buffer after swapping. Draw every visible line
       and commit exactly once; student callbacks must not call tft_update. */
    tft_update(0);
}
