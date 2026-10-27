#ifndef TUTORIAL_JOYSTICK_H
#define TUTORIAL_JOYSTICK_H
#include <stdbool.h>
#include <stdint.h>
/* Called once, after the generated peripheral initialization. */
bool Joystick_Start(void);
/* On failure, return false and leave *raw unchanged. */
bool Joystick_ReadChannel(uint32_t channel, uint16_t *raw);
#endif
