/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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

void judge(void);
int change(int hexnum);
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define servo_TX_Pin GPIO_PIN_2
#define servo_TX_GPIO_Port GPIOA
#define servo_RX_Pin GPIO_PIN_3
#define servo_RX_GPIO_Port GPIOA
#define move_IN1_Pin GPIO_PIN_4
#define move_IN1_GPIO_Port GPIOA
#define move_IN2_Pin GPIO_PIN_5
#define move_IN2_GPIO_Port GPIOA
#define move_IN3_Pin GPIO_PIN_6
#define move_IN3_GPIO_Port GPIOA
#define move_IN4_Pin GPIO_PIN_7
#define move_IN4_GPIO_Port GPIOA
#define KEY0_Pin GPIO_PIN_5
#define KEY0_GPIO_Port GPIOC
#define KEY0_EXTI_IRQn EXTI9_5_IRQn
#define bujin1_con_Pin GPIO_PIN_0
#define bujin1_con_GPIO_Port GPIOB
#define bujin2_con_Pin GPIO_PIN_1
#define bujin2_con_GPIO_Port GPIOB
#define bujin3_con_Pin GPIO_PIN_2
#define bujin3_con_GPIO_Port GPIOB
#define move_back_INA_Pin GPIO_PIN_10
#define move_back_INA_GPIO_Port GPIOB
#define move_back_INB_Pin GPIO_PIN_11
#define move_back_INB_GPIO_Port GPIOB
#define bujin4_con_Pin GPIO_PIN_12
#define bujin4_con_GPIO_Port GPIOB
#define move_back_IN3_Pin GPIO_PIN_13
#define move_back_IN3_GPIO_Port GPIOB
#define move_back_IN2_Pin GPIO_PIN_14
#define move_back_IN2_GPIO_Port GPIOB
#define move_back_IN1_Pin GPIO_PIN_15
#define move_back_IN1_GPIO_Port GPIOB
#define bujin1_PWM_Pin GPIO_PIN_6
#define bujin1_PWM_GPIO_Port GPIOC
#define bujin2_PWM_Pin GPIO_PIN_7
#define bujin2_PWM_GPIO_Port GPIOC
#define bujin3_PWM_Pin GPIO_PIN_8
#define bujin3_PWM_GPIO_Port GPIOC
#define bujin_4_PWM_Pin GPIO_PIN_9
#define bujin_4_PWM_GPIO_Port GPIOC
#define move_ENA_Pin GPIO_PIN_8
#define move_ENA_GPIO_Port GPIOA
#define tjc_TX_Pin GPIO_PIN_9
#define tjc_TX_GPIO_Port GPIOA
#define tjc_RX_Pin GPIO_PIN_10
#define tjc_RX_GPIO_Port GPIOA
#define move_ENB_Pin GPIO_PIN_11
#define move_ENB_GPIO_Port GPIOA
#define move_back_IN4_Pin GPIO_PIN_10
#define move_back_IN4_GPIO_Port GPIOC
#define LED1_Pin GPIO_PIN_2
#define LED1_GPIO_Port GPIOD
#define bianmaIN1_Pin GPIO_PIN_5
#define bianmaIN1_GPIO_Port GPIOB
#define bianma_IN2_Pin GPIO_PIN_6
#define bianma_IN2_GPIO_Port GPIOB
#define bianma_IN3_Pin GPIO_PIN_8
#define bianma_IN3_GPIO_Port GPIOB
#define bianma_IN4_Pin GPIO_PIN_9
#define bianma_IN4_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */
extern int hangju;
extern int zhuju;
extern uint16_t ITjishu;

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
