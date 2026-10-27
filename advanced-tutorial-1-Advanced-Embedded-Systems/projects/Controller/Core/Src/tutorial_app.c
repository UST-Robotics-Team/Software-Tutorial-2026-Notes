#include "tutorial_app.h"
#include "student_tasks.h"
#include "joystick.h"
#include "joystick_config.h"
#include "joystick_normalization.h"
#include "main.h"
#include "lcd/lcd.h"
#include <math.h>
static bool adc_ready;
static uint32_t last_update;
volatile float g_joystick_normalized[4];
volatile float g_joystick_push[2];
void TutorialApp_Init(void)
{
    adc_ready = Joystick_Start();
    last_update = HAL_GetTick() - 100U;
}
static unsigned Hundredths(float value)
{
    return (unsigned)(fabsf(value) * 100.0f + 0.5f);
}
static void DrawAxis(uint8_t row, const char *name, uint16_t raw, float value)
{
    unsigned n = Hundredths(value);
    /* Integer formatting avoids dependence on the TFT mini-printf float path. */
    tft_prints(0, row, "%s:%4u %c%u.%02u", name, (unsigned)raw,
               value < 0.0f ? '-' : '+', n / 100U, n % 100U);
}
static void DrawFrame(void)
{
    tft_prints(0, 0, "CW1 NORMALIZED");
    tft_prints(0, 9, "RUN %u s", (unsigned)(HAL_GetTick() / 1000U));
    if (!adc_ready) {
        tft_prints(0, 1, "ADC NOT READY");
        tft_prints(0, 2, "CHECK CW1A SETUP");
        return;
    }
    uint16_t raw[4] = {0};
    if (!CW1_ReadJoystick(raw)) {
        tft_prints(0, 1, "READ NOT READY");
        tft_prints(0, 2, "CHECK CW1A READ");
        return;
    }
    for (unsigned i = 0; i < JOYSTICK_AXIS_COUNT; ++i) {
        if (raw[i] > 4095U) {
            tft_prints(0, 1, "BAD RAW VALUE");
            return;
        }
    }
    const uint16_t minimum[4] = {J1_X_MIN,J1_Y_MIN,J2_X_MIN,J2_Y_MIN};
    const uint16_t centre[4] = {J1_X_CENTRE,J1_Y_CENTRE,J2_X_CENTRE,J2_Y_CENTRE};
    const uint16_t maximum[4] = {J1_X_MAX,J1_Y_MAX,J2_X_MAX,J2_Y_MAX};
    const int direction[4] = {1, J1_Y_DIRECTION, 1, J2_Y_DIRECTION};
    float axis[4] = {0};
    for (unsigned i=0; i<JOYSTICK_AXIS_COUNT; ++i) {
        axis[i] = CW1_NormalizeAxis(raw[i],minimum[i],centre[i],maximum[i],JOYSTICK_DEADBAND) * (float)direction[i];
        if (!isfinite(axis[i]) || axis[i] < -1.0f || axis[i] > 1.0f) {
            tft_prints(0, 1, "CHECK CW1B MATH");
            return;
        }
        g_joystick_normalized[i] = axis[i];
    }
    DrawAxis(1,"J1X",raw[0],axis[0]);
    if (JOYSTICK_AXIS_COUNT == 1U) {
        tft_prints(0, 2, "J1Y:---- --");
        tft_prints(0, 3, "J1 PUSH: --");
        tft_prints(0, 5, "J2X:---- --");
        tft_prints(0, 6, "J2Y:---- --");
        tft_prints(0, 7, "J2 PUSH: --");
        tft_prints(0, 8, "1 AXIS RAW VALID");
        return;
    }
    float j1 = Joystick_PushExtent(axis[0],axis[1]);
    float j2 = Joystick_PushExtent(axis[2],axis[3]);
    g_joystick_push[0] = j1; g_joystick_push[1] = j2;
    DrawAxis(2,"J1Y",raw[1],axis[1]);
    unsigned n = Hundredths(j1);
    tft_prints(0,3,"J1 PUSH:%u.%02u",n/100U,n%100U);
    DrawAxis(5,"J2X",raw[2],axis[2]); DrawAxis(6,"J2Y",raw[3],axis[3]);
    n = Hundredths(j2);
    tft_prints(0,7,"J2 PUSH:%u.%02u",n/100U,n%100U);
    tft_prints(0,8,"4 AXES RAW VALID");
}
void TutorialApp_Update(void)
{
    uint32_t now = HAL_GetTick();
    if ((uint32_t)(now-last_update) < 100U) return;
    last_update = now;
    DrawFrame();
    tft_update(0);
}
