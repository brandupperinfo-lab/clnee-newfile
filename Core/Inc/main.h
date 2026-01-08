/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "stm32g0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "bsp.h"
#include "ACIO.h"
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
#define PRELOAD_VALUE 400
#define H_SENSE_Pin GPIO_PIN_7
#define H_SENSE_GPIO_Port GPIOB
#define CHRG_LED_Pin GPIO_PIN_9
#define CHRG_LED_GPIO_Port GPIOB
#define H_EN_Pin GPIO_PIN_15
#define H_EN_GPIO_Port GPIOC
#define BUTTON_Pin GPIO_PIN_0
#define BUTTON_GPIO_Port GPIOA
#define CHRG_STAT_1_Pin GPIO_PIN_1
#define CHRG_STAT_1_GPIO_Port GPIOA
#define VUSB_DIV_Pin GPIO_PIN_2
#define VUSB_DIV_GPIO_Port GPIOA
#define CHRG_CTRL_Pin GPIO_PIN_3
#define CHRG_CTRL_GPIO_Port GPIOA
#define VBAT_DIV_Pin GPIO_PIN_4
#define VBAT_DIV_GPIO_Port GPIOA
#define ISENSE_Pin GPIO_PIN_5
#define ISENSE_GPIO_Port GPIOA
#define STAT_IND_Pin GPIO_PIN_6
#define STAT_IND_GPIO_Port GPIOA
#define PL_Pin GPIO_PIN_7
#define PL_GPIO_Port GPIOA
#define PH_Pin GPIO_PIN_8
#define PH_GPIO_Port GPIOA
#define UV_EN_Pin GPIO_PIN_11
#define UV_EN_GPIO_Port GPIOA
#define NTC_Pin GPIO_PIN_12
#define NTC_GPIO_Port GPIOA
#define UV_IND_Pin GPIO_PIN_5
#define UV_IND_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
