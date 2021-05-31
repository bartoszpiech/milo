/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
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
#include "stm32f3xx_hal.h"

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
#define TIM15_PWM_PRESCALER 71
#define TIM15_PWM_PERIOD 19999
#define TIM16_PWM_PRESCALER 71
#define TIM16_PWM_PERIOD 19999
#define TIM17_PWM_PRESCALER 71
#define TIM17_PWM_PERIOD 19999
#define TIM3_PWM_PRESCALER 71
#define TIM3_PWM_PERIOD 19999
#define TIM6_PRINT_PRESCALER 7199
#define TIM6_PRINT_PERIOD 9999
#define B1_Pin GPIO_PIN_13
#define B1_GPIO_Port GPIOC
#define RCC_OSC32_OUT_Pin GPIO_PIN_15
#define RCC_OSC32_OUT_GPIO_Port GPIOC
#define ENCODER_CH1_Pin GPIO_PIN_0
#define ENCODER_CH1_GPIO_Port GPIOA
#define ENCODER_CH2_Pin GPIO_PIN_1
#define ENCODER_CH2_GPIO_Port GPIOA
#define USART_TX_Pin GPIO_PIN_2
#define USART_TX_GPIO_Port GPIOA
#define USART_RX_Pin GPIO_PIN_3
#define USART_RX_GPIO_Port GPIOA
#define ENCODER_BUTTON_Pin GPIO_PIN_4
#define ENCODER_BUTTON_GPIO_Port GPIOA
#define ENCODER_BUTTON_EXTI_IRQn EXTI4_IRQn
#define LD2_Pin GPIO_PIN_5
#define LD2_GPIO_Port GPIOA
#define SERVO3_PWM_Pin GPIO_PIN_6
#define SERVO3_PWM_GPIO_Port GPIOA
#define SERVO4_PWM_Pin GPIO_PIN_7
#define SERVO4_PWM_GPIO_Port GPIOA
#define SERVO2_PWM_Pin GPIO_PIN_14
#define SERVO2_PWM_GPIO_Port GPIOB
#define SERVO1_PWM_Pin GPIO_PIN_6
#define SERVO1_PWM_GPIO_Port GPIOC
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
