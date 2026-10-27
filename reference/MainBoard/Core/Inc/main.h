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
#include "stm32f4xx_hal.h"

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
#define LED_D5_Pin GPIO_PIN_14
#define LED_D5_GPIO_Port GPIOC
#define LED_D6_Pin GPIO_PIN_15
#define LED_D6_GPIO_Port GPIOC
#define LED_D7_Pin GPIO_PIN_0
#define LED_D7_GPIO_Port GPIOC
#define LED_D8_Pin GPIO_PIN_1
#define LED_D8_GPIO_Port GPIOC
#define US_TRIG_Pin GPIO_PIN_0
#define US_TRIG_GPIO_Port GPIOA
#define US_ECHO_Pin GPIO_PIN_1
#define US_ECHO_GPIO_Port GPIOA
#define IR_D0_UART2_T_Pin GPIO_PIN_2
#define IR_D0_UART2_T_GPIO_Port GPIOA
#define IR_A0_UART2_R_Pin GPIO_PIN_3
#define IR_A0_UART2_R_GPIO_Port GPIOA
#define BTN2_Pin GPIO_PIN_4
#define BTN2_GPIO_Port GPIOA
#define TFT_SCK_Pin GPIO_PIN_5
#define TFT_SCK_GPIO_Port GPIOA
#define TFT_RES_Pin GPIO_PIN_6
#define TFT_RES_GPIO_Port GPIOA
#define TFT_MOSI_Pin GPIO_PIN_7
#define TFT_MOSI_GPIO_Port GPIOA
#define TFT_DC_Pin GPIO_PIN_4
#define TFT_DC_GPIO_Port GPIOC
#define TFT_CS_Pin GPIO_PIN_5
#define TFT_CS_GPIO_Port GPIOC
#define TFT_BL_Pin GPIO_PIN_0
#define TFT_BL_GPIO_Port GPIOB
#define BTN1_Pin GPIO_PIN_1
#define BTN1_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */
#define __forceinline __attribute__((__always_inline__)) inline

#define gpio_set(gpio) HAL_GPIO_WritePin(gpio##_GPIO_Port, gpio##_Pin, GPIO_PIN_SET)
#define gpio_reset(gpio) HAL_GPIO_WritePin(gpio##_GPIO_Port, gpio##_Pin, GPIO_PIN_RESET)
#define gpio_toggle(gpio) HAL_GPIO_TogglePin(gpio##_GPIO_Port, gpio##_Pin)
#define gpio_read(gpio) HAL_GPIO_ReadPin(gpio##_GPIO_Port, gpio##_Pin)
#define led_on(led) gpio_reset(led)
#define led_off(led) gpio_set(led)
#define led_toggle(led) gpio_toggle(led)
#define btn_read(btn) (gpio_read(btn) == GPIO_PIN_RESET)

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
