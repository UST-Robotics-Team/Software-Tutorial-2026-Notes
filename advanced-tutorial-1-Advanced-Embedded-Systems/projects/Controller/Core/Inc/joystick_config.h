#ifndef JOYSTICK_CONFIG_H
#define JOYSTICK_CONFIG_H
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
