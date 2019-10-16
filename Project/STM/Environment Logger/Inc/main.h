/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
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
#include "stm32f0xx_hal.h"

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
#define SHDN 0x10
#define GA 0x20
#define BUF 0x40
#define SNGL 0x80
#define CH0 0x00
#define CH1 0x10
#define CH2 0x20
#define RTC_ADDR 0x6F
#define RTC_SEC_ADDR 0x00
#define RTC_MIN_ADDR 0x01
#define RTC_HOUR_ADDR 0x02
#define RTC_WEEKDAY_ADDR 0x03
#define RTC_DATE_ADDR 0x04
#define RTC_MONTH_ADDR 0x05
#define RTC_YEAR_ADDR 0x06
#define SW0_Pin GPIO_PIN_0
#define SW0_GPIO_Port GPIOA
#define SW0_EXTI_IRQn EXTI0_1_IRQn
#define SW1_Pin GPIO_PIN_1
#define SW1_GPIO_Port GPIOA
#define SW1_EXTI_IRQn EXTI0_1_IRQn
#define SW2_Pin GPIO_PIN_2
#define SW2_GPIO_Port GPIOA
#define SW2_EXTI_IRQn EXTI2_3_IRQn
#define SW3_Pin GPIO_PIN_3
#define SW3_GPIO_Port GPIOA
#define SW3_EXTI_IRQn EXTI2_3_IRQn
#define DAC_Pin GPIO_PIN_4
#define DAC_GPIO_Port GPIOA
#define LED0_Pin GPIO_PIN_0
#define LED0_GPIO_Port GPIOB
#define LED1_Pin GPIO_PIN_1
#define LED1_GPIO_Port GPIOB
#define LED3_Pin GPIO_PIN_2
#define LED3_GPIO_Port GPIOB
#define ADC_Pin GPIO_PIN_8
#define ADC_GPIO_Port GPIOA
#define LED3B3_Pin GPIO_PIN_3
#define LED3B3_GPIO_Port GPIOB
#define LED4_Pin GPIO_PIN_4
#define LED4_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
