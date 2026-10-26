#include "joystick_normalization.h"
#include <math.h>
float Joystick_PushExtent(float x, float y)
{
    if (!isfinite(x) || !isfinite(y)) return 0.0f;
    /* Inputs normally come from NormalizeAxis; clamp before squaring. */
    x = fminf(1.0f, fmaxf(-1.0f, x));
    y = fminf(1.0f, fmaxf(-1.0f, y));
    float magnitude = sqrtf(x*x + y*y);
    return magnitude > 1.0f ? 1.0f : magnitude;
}
