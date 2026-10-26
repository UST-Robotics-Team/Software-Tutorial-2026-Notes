#ifndef JOYSTICK_NORMALIZATION_H
#define JOYSTICK_NORMALIZATION_H
#include <stdint.h>
/* Circular stick magnitude, clamped to [0,1]. Non-finite inputs return zero. */
float Joystick_PushExtent(float x, float y);
#endif
