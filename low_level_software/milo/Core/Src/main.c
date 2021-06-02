/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include <stdio.h>
#include <stdlib.h>
#include "servo.h"
#include "manipulator.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

#define IS_NUMERIC_STRING(d) (*(char*)d >= 48) && (*(char*)d<= 57)
#define CONVERSION(d,k)  ((d<<3) +(d<<1))+(*(char*)k-48);

uint32_t
string_to_int(uint8_t *pszBuffer) {
    uint32_t u32Number=0;
    while( IS_NUMERIC_STRING(pszBuffer)) {
        u32Number=CONVERSION(u32Number,pszBuffer);
        pszBuffer++;
    }
    return u32Number;
}

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

UART_HandleTypeDef huart2;
uint32_t button = 0;
uint8_t message;
uint8_t set[5];
int16_t enc_val;
manipulator_t milo = { 0 };
uint16_t servo_angle[3] = { 0 };

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

int
_write(int file, uint8_t *ptr, int len) {
	HAL_UART_Transmit_IT(&huart2, ptr, len);
	return len;
}

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_USART2_UART_Init();
  MX_TIM2_Init();
  MX_TIM15_Init();
  MX_TIM16_Init();
  MX_TIM17_Init();
  MX_TIM3_Init();
  MX_TIM6_Init();
  /* USER CODE BEGIN 2 */

  //HAL_TIM_Base_Start_IT(&htim6); // debug
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim15, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim16, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim17, TIM_CHANNEL_1);
  HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_1);
  HAL_UART_Receive_IT(&huart2, &message, 1);

  manipulator_init(&milo);
  /*
  servo_init(&(milo->ft[0], htim15, TIM_CHANNEL_1, 0, 0, 1800, 500, 2500);
  servo_init(&(milo->ft[1], htim16, TIM_CHANNEL_1, 0, 0, 1800, 500, 2500);
  servo_init(&(milo->ft[2], htim17, TIM_CHANNEL_1, 0, 0, 1800, 500, 2500);
  */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

	  /*
	if (HAL_GPIO_ReadPin(ENCODER_BUTTON_GPIO_Port, ENCODER_BUTTON_Pin)) {
		button++;
		printf("Odczyt: %ld; Przycisk: %ld\r\n", count, button);
		HAL_Delay(50);
		while (!HAL_GPIO_ReadPin(ENCODER_BUTTON_GPIO_Port, ENCODER_BUTTON_Pin));
	}
	*/

	 // sprawdzenie overflow
	  /*
	 enc_val = __HAL_TIM_GET_COUNTER(&htim2);
	 if (enc_val < 0) {
		 enc_val = 0;
	 } else if (enc_val > 180) {
		 enc_val = 180;
	 }
	 */
	  /*
	 servo_angle[button]= enc_val;
	 servo_set(&ft[0], servo_angle[0] * 10, 0);
	 servo_set(&ft[1], servo_angle[1] * 10, 0);
	 servo_set(&ft[2], servo_angle[2] * 10, 0);
	 */
	 //printf("servo[0]: %d; servo[1]: %d; servo[2]: %d; Przycisk: %d\r\n", servo_angle[0], servo_angle[1], servo_angle[2], button);
	 manipulator_update(&milo);
	 //rintf("q1 = %d, q2 = %d, q3 = %d, x = %d, y = %d, z = %d\r\n", (int)(milo.q[0] * 180 / M_PI), (int)(milo.q[1] * 180 / M_PI), (int)(milo.q[2] * 180 / M_PI), (int)milo.effector.x, (int)milo.effector.y, (int)milo.effector.z);
	 HAL_Delay(10);
	 //servo_set(&milo.mg, 0, 0);
	 //HAL_Delay(3000);
	 //servo_set(&milo.mg, 1800, 0);
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

void
HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	if (GPIO_Pin == ENCODER_BUTTON_Pin) {
		button++;
		button = button % 3;
		__HAL_TIM_SET_COUNTER(&htim2, servo_angle[button]);
	}

}

void
HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	if (huart->Instance == USART2) {
		if (message == 'b') {
			printf("b %ld;\r\n", button);
		} else if (message == 'c') {
			uint8_t button_number;
			HAL_UART_Receive(huart, &button_number, 1, 10);
			button = button_number - '0';
			printf("c %ld;\r\n", button);
		} else if (message == 'e') {
			printf("e %ld;\r\n", __HAL_TIM_GET_COUNTER(&htim2));
		} else if (message == 'a') {
			uint8_t servo_number, semicolon;
			HAL_UART_Receive(huart, &servo_number, 1, 10);
			HAL_UART_Receive(huart, &semicolon, 1, 10);	// semicolon
			printf("a%c %d;\r\n", servo_number, servo_angle[servo_number - '0']);
		} else if (message == 'd') {
			uint8_t semicolon;
			HAL_UART_Receive(huart, &semicolon, 1, 10);	// semicolon
			printf("d;%d;%d;%d;\r\n", servo_angle[0], servo_angle[1], servo_angle[2]);
		} else if (message == 's') {
			uint8_t set_servo_number, tmp, set_servo_angle_str[4];
			uint8_t set_servo_angle_int;
			HAL_UART_Receive(huart, &set_servo_number, 1, 10);
			HAL_UART_Receive(huart, &tmp, 1, 10); // space
			for (uint8_t i = 0; i < 4; i++) {
			HAL_UART_Receive(huart, &tmp, 1, 10);
				if (tmp == ';') {
					set_servo_angle_str[i] = 0;
					break;
				}
				set_servo_angle_str[i] = tmp;
			}
			set_servo_angle_int = string_to_int(set_servo_angle_str);
			if (set_servo_angle_int > 180) {
				set_servo_angle_int = 180;
				printf("zbyt duzy kat\r\n");
			} else if (set_servo_angle_int < 0) {
				set_servo_angle_int = 0;
				printf("zbyt maly kat\r\n");
			}
			servo_angle[set_servo_number - '0'] = set_servo_angle_int;
			if (set_servo_number - '0' == button) {
				__HAL_TIM_SET_COUNTER(&htim2, set_servo_angle_int);
			}
			printf("s%c %d;\r\n", set_servo_number, set_servo_angle_int);
		} else if (message == 'h') {
			milo.effector.x--;
		} else if (message == 'y') {
			milo.effector.x++;
		} else if (message == 'j') {
			milo.effector.y--;
		} else if (message == 'u') {
			milo.effector.y++;
		} else if (message == 'k') {
			milo.effector.z--;
		} else if (message == 'i') {
			milo.effector.z++;
		} else if (message == 'o') {
			milo.effector.x = 49.0;
			milo.effector.y = 29.0;
			milo.effector.z = 0.0;
		} else {
			printf("Niepoprawne dane\r\n");
		}
		HAL_UART_Receive_IT(huart, &message, 1);
	}
}

void
HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	if (htim == &htim6) {	// wyswietlanie aktualnych danych do debugu
		printf("a0: %d; a1: %d; a2: %d; b: %ld\r\n", servo_angle[0], servo_angle[1], servo_angle[2], button);
	}
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
