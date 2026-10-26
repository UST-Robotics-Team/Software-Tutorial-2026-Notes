#include "joystick_normalization.h"
#include <math.h>
float Joystick_NormalizeAxis(uint16_t raw, uint16_t minimum, uint16_t centre,
                            uint16_t maximum, uint16_t deadband)
{
    int32_t left = (int32_t)centre - minimum;
    int32_t right = (int32_t)maximum - centre;
    if (left <= (int32_t)deadband || right <= (int32_t)deadband) return 0.0f;
    int32_t delta = (int32_t)raw - centre;
    if (delta >= -(int32_t)deadband && delta <= (int32_t)deadband) return 0.0f;
    float value;
    if (delta > 0)
        value = (float)(delta - deadband) / (float)(right - deadband);
    else
        value = (float)(delta + deadband) / (float)(left - deadband);
    if (value > 1.0f) return 1.0f;
    if (value < -1.0f) return -1.0f;
    return value;
}
float Joystick_PushExtent(float x, float y)
{
    if (!isfinite(x) || !isfinite(y)) return 0.0f;
    /* Inputs normally come from NormalizeAxis; clamp before squaring. */
    x = fminf(1.0f, fmaxf(-1.0f, x));
    y = fminf(1.0f, fmaxf(-1.0f, y));
    float magnitude = sqrtf(x*x + y*y);
    return magnitude > 1.0f ? 1.0f : magnitude;
}
