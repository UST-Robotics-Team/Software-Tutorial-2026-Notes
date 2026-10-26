/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
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
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define Joystick1_Button_Pin GPIO_PIN_14
#define Joystick1_Button_GPIO_Port GPIOC
#define Joystick2_Button_Pin GPIO_PIN_15
#define Joystick2_Button_GPIO_Port GPIOC
#define Joystick1_X_Pin GPIO_PIN_0
#define Joystick1_X_GPIO_Port GPIOA
#define Joystick1_Y_Pin GPIO_PIN_1
#define Joystick1_Y_GPIO_Port GPIOA
#define Joystick2_X_Pin GPIO_PIN_2
#define Joystick2_X_GPIO_Port GPIOA
#define Joystick2_Y_Pin GPIO_PIN_3
#define Joystick2_Y_GPIO_Port GPIOA
#define ADC1_IN4_Pin GPIO_PIN_4
#define ADC1_IN4_GPIO_Port GPIOA
#define TFT_SCK_Pin GPIO_PIN_5
#define TFT_SCK_GPIO_Port GPIOA
#define TFT_MOSI_Pin GPIO_PIN_7
#define TFT_MOSI_GPIO_Port GPIOA
#define BOOT1_Pin GPIO_PIN_2
#define BOOT1_GPIO_Port GPIOB
#define TFT_RES_Pin GPIO_PIN_10
#define TFT_RES_GPIO_Port GPIOB
#define TFT_DC_Pin GPIO_PIN_11
#define TFT_DC_GPIO_Port GPIOB
#define TFT_CS_Pin GPIO_PIN_12
#define TFT_CS_GPIO_Port GPIOB
#define TFT_BL_Pin GPIO_PIN_13
#define TFT_BL_GPIO_Port GPIOB
#define Button4_Pin GPIO_PIN_14
#define Button4_GPIO_Port GPIOB
#define Button3_Pin GPIO_PIN_15
#define Button3_GPIO_Port GPIOB
#define Button2_Pin GPIO_PIN_8
#define Button2_GPIO_Port GPIOA
#define Button1_Pin GPIO_PIN_9
#define Button1_GPIO_Port GPIOA
#define LimitSwitch2_Pin GPIO_PIN_11
#define LimitSwitch2_GPIO_Port GPIOA
#define LimitSwitch1_Pin GPIO_PIN_12
#define LimitSwitch1_GPIO_Port GPIOA
#define Button8_Pin GPIO_PIN_15
#define Button8_GPIO_Port GPIOA
#define Button7_Pin GPIO_PIN_3
#define Button7_GPIO_Port GPIOB
#define Button6_Pin GPIO_PIN_4
#define Button6_GPIO_Port GPIOB
#define Button5_Pin GPIO_PIN_5
#define Button5_GPIO_Port GPIOB
#define LED2_Pin GPIO_PIN_8
#define LED2_GPIO_Port GPIOB
#define LED1_Pin GPIO_PIN_9
#define LED1_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
