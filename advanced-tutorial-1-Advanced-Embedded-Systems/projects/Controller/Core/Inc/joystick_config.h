#ifndef JOYSTICK_CONFIG_H
#define JOYSTICK_CONFIG_H
/* CW1A: first read J1X only; change to 4 after enabling PA1-PA3 in CubeMX. */
#define JOYSTICK_AXIS_COUNT 1U
#if JOYSTICK_AXIS_COUNT != 1U && JOYSTICK_AXIS_COUNT != 4U
#error "JOYSTICK_AXIS_COUNT must be 1 or 4"
#endif
/* Starting values, not measured calibration. Measure each centre and endpoint. */
#define J1_X_MIN 0U
#define J1_X_MAX 4095U
#define J1_X_CENTRE 2048U
#define J1_Y_MIN 0U
#define J1_Y_MAX 4095U
#define J1_Y_CENTRE 2048U
#define J2_X_MIN 0U
#define J2_X_MAX 4095U
#define J2_X_CENTRE 2048U
#define J2_Y_MIN 0U
#define J2_Y_MAX 4095U
#define J2_Y_CENTRE 2048U
/* Physical Y polarity: -1 reverses the ADC-positive direction. */
#define J1_Y_DIRECTION (-1)
#define J2_Y_DIRECTION (-1)
#define JOYSTICK_DEADBAND 120U
#endif
