#include "student_tasks.h"
#include "joystick.h"
#include "joystick_config.h"
/* Add adc.h after generating ADC1; use its ADC_CHANNEL_* constants in CW1A. */

bool CW1_ReadJoystick(uint16_t values[4])
{
    /* TODO CW1A: use your Joystick_ReadChannel() for JOYSTICK_AXIS_COUNT axes.
       Return true only when every requested reading succeeds.
       A one-axis attempt writes values[0] only; four-axis order is J1X/J1Y/J2X/J2Y. */
    (void)values;
    return false;
}
float CW1_NormalizeAxis(uint16_t raw, uint16_t minimum, uint16_t centre,
                       uint16_t maximum, uint16_t deadband)
{
    /* TODO CW1B: map the measured range to a continuous signed position.
       Return zero in the inclusive centre deadband and for invalid spans.
       Use the five parameters and keep the result within [-1,1].
       The app applies Y direction once and supplies PUSH.
       CW1C: measure calibration and choose a deadband in joystick_config.h. */
    (void)raw; (void)minimum; (void)centre; (void)maximum; (void)deadband;
    return 0.0f;
}
