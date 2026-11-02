#ifndef __MAINBOARD_RM_MOTOR_H
#define __MAINBOARD_RM_MOTOR_H

#include "can.h"

#define RM_CURRENT_MAX      20.0f
#define RM_CURRENT_RAW_MAX  16384
#define RM_CURRENT_SOFT_MAX 5.0f

#define RM_CAN_TX_GRP1_ID 0x200
#define RM_CAN_TX_GRP2_ID 0x1FF

#define RM_CAN_RX_ID_BASE 0x201

/**
 * ID of the RM Motor
 *
 * This corresponds to the RM ESC ID (i.e. the number of times the led blinks)
 * This ID is **separate** between different CAN buses
 */
typedef enum {
  RM_MOTOR_1 = 0,
  RM_MOTOR_2,
  RM_MOTOR_3,
  RM_MOTOR_4,
  RM_MOTOR_5,
  RM_MOTOR_6,
  RM_MOTOR_7,
  RM_MOTOR_8,
  NUM_OF_RM_MOTORS, /**< Total number of RM motors */
} RM_Motor;

/**
 * Feedback from the RM Motor
 */
typedef struct {
  float current;       /**< Current of the motor (unit: A) */
  uint16_t encoder;    /**< Raw reading of the encoder (0 ~ 8191 in one revolution before gearing) */
  int16_t vel_rpm;     /**< Angular velocity of the rotor before gearing (unit: rpm) */
  int16_t raw_current; /**< Raw current value (-16384 ~ 16384) */
  uint8_t temperature; /**< Temperature (unit: degree C) */
} RM_Feedback;

/**
 * Initialize the CAN bus for communication with RM motors.
 * @param hcan The CAN handle where RM motors are connected
 */
void rm_can_init(CAN_HandleTypeDef* hcan);

/**
 * The control loop for the RM motors.
 * @param hcan The CAN handle where RM motors are connected
 *
 * This function should be called in the main loop of the program at regular intervals.
 */
void rm_ctrl_loop(CAN_HandleTypeDef* hcan);

/**
 * Set the target current for a specific RM motor.
 * @param hcan The CAN handle where RM motors are connected
 * @param motor The RM motor to set the current for (unit: A)
 */
void rm_set_current_setpoint(CAN_HandleTypeDef* hcan, RM_Motor motor, float current);

/**
 * Get the target current for a specific RM motor.
 * @param hcan The CAN handle where RM motors are connected
 * @return The target current for the specified RM motor (unit: A)
 */
float rm_get_current_setpoint(CAN_HandleTypeDef* hcan, RM_Motor motor);

/**
 * Get the complete feedback from a specific RM motor.
 * @param hcan The CAN handle where RM motors are connected
 * @param motor The RM motor to get feedback from
 * @return The feedback from the specified RM motor
 */
const volatile RM_Feedback* rm_get_feedback(CAN_HandleTypeDef* hcan, RM_Motor motor);

/**
 * Get the encoder value from a specific RM motor.
 * @param hcan The CAN handle where RM motors are connected
 * @param motor The RM motor to get the encoder value from
 * @return The encoder value from the specified RM motor (unit: raw value)
 */
uint16_t rm_get_encoder(CAN_HandleTypeDef* hcan, RM_Motor motor);

/**
 * Get the actual velocity from a specific RM motor.
 * @param hcan The CAN handle where RM motors are connected
 * @param motor The RM motor to get the actual velocity from
 * @return The actual velocity from the specified RM motor (unit: rpm)
 */
int16_t rm_get_actual_vel(CAN_HandleTypeDef* hcan, RM_Motor motor);

/**
 * Get the actual current from a specific RM motor.
 * @param hcan The CAN handle where RM motors are connected
 * @param motor The RM motor to get the actual current from
 * @return The actual current from the specified RM motor (unit: A)
 */
float rm_get_actual_current(CAN_HandleTypeDef* hcan, RM_Motor motor);

/**
 * Get the temperature from a specific RM motor.
 * @param hcan The CAN handle where RM motors are connected
 * @param motor The RM motor to get the temperature from
 */
uint8_t rm_get_temperature(CAN_HandleTypeDef* hcan, RM_Motor motor);

#endif
