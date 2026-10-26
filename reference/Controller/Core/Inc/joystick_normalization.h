#ifndef JOYSTICK_NORMALIZATION_H
#define JOYSTICK_NORMALIZATION_H
#include <stdint.h>
/* Piecewise linear signed position, continuous outside the centre deadband.
   Invalid calibration returns zero. Values beyond either endpoint are clamped. */
float Joystick_NormalizeAxis(uint16_t raw, uint16_t minimum, uint16_t centre,
                            uint16_t maximum, uint16_t deadband);
/* Circular stick magnitude, clamped to [0,1]. Non-finite inputs return zero. */
float Joystick_PushExtent(float x, float y);
#endif
