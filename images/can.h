/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file    can.h
 * @brief   This file contains all the function prototypes for
 *          the can.c file
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CAN_H__
#define __CAN_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern CAN_HandleTypeDef hcan1;

extern CAN_HandleTypeDef hcan2;

/* USER CODE BEGIN Private defines */

typedef enum {
	CAN1_MOTOR0,
	CAN1_MOTOR1,
	CAN1_MOTOR2,
	CAN1_MOTOR3,
	CAN1_MOTOR4,
	CAN1_MOTOR5,
	CAN1_MOTOR6,
	CAN1_MOTOR7,
	CAN2_MOTOR0,
	CAN2_MOTOR1,
	CAN2_MOTOR2,
	CAN2_MOTOR3,
	CAN2_MOTOR4,
	CAN2_MOTOR5,
	CAN2_MOTOR6,
	CAN2_MOTOR7,
	MAX_NUM_OF_MOTORS
} Motor;

typedef enum {
	CAN_GROUP_ID = 0x200,
	CAN_3508_M1_ID,
	CAN_3508_M2_ID,
	CAN_3508_M3_ID,
	CAN_3508_M4_ID,
	CAN_3508_M5_ID,
	CAN_3508_M6_ID,
	CAN_3508_M7_ID,
	CAN_3508_M8_ID,
} can_msg_id_e;

typedef struct {
	uint16_t encoder;
	int16_t vel_rpm;
	int16_t raw_current;
	uint8_t temperature;
} MotorFeedback;

typedef struct {
	uint16_t encoder;
	int16_t vel_rpm;
	float actual_current;
	uint8_t temperature;
} MotorStats;

#define MAX_CAN_RM		 8
#define NUM_OF_CAN		 2
#define RM_TX_GRP1_ID	 0x200
#define RM_TX_GRP2_ID	 0x1FF
#define MOTOR_SPEED_MAX	 16384
#define CAN_DATA_SIZE	 8
#define CAN1_RX_ID_START 0x201
#define MOTOR_ID		 2
/* USER CODE END Private defines */
void MX_CAN1_Init(void);
void MX_CAN2_Init(void);

/* USER CODE BEGIN Prototypes */
void can_filter_enable(CAN_HandleTypeDef *hcan);
void can_filter_disable(CAN_HandleTypeDef *hcan);
void can_transmit(CAN_HandleTypeDef *hcan, uint16_t id, int16_t msg1, int16_t msg2, int16_t msg3, int16_t msg4);
void can_filter_init();
void can_init();
void can_ctrl_loop();
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan);

/* USER FUNCTONS */

/**
 * @brief Returns motor feedback stats for a specific motor
 **/
MotorStats get_motor_feedback(Motor tar_motor);

/**
 * @brief Clockwise if current if is positive, and vice versa. Max current is
 *16384.
 **/
void set_motor_current(Motor tar_motor, int16_t tar_current);

// TODO: implement this (Tips: see PID notes)
void set_motor_speed(Motor tar_motor, int16_t tar_vel);

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __CAN_H__ */
