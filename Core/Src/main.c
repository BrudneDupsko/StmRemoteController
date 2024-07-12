/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

uint32_t ICValue2 = 0;
uint32_t ICValue22 = 0;
uint32_t Frequency1 = 0;
int Duty2 = 0;

uint32_t ICValue1 = 0;
uint32_t ICValue12 = 0;
uint32_t Frequency2 = 0;
uint32_t Duty1 = 0;

uint32_t ICValue6 = 0;
uint32_t ICValue62 = 0;
int Frequency3 = 0;
int Duty6 = 0;


uint32_t ICValue3 = 0;
uint32_t ICValue32 = 0;
int Frequency4 = 0;
int Duty3 = 0;

uint32_t ICValue5 = 0;
uint32_t ICValue52 = 0;
int Frequency5 = 0;
int Duty5 = 0;


uint32_t ICValue4 = 0;
uint32_t ICValue42 = 0;
int Frequency6 = 0;
int Duty4 = 0;

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	if (htim == &htim1)
	{
	if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)  // If the interrupt is triggered by channel 1
	{
		// Read the IC value
		ICValue2 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);

		if (ICValue2 != 0)
		{
			ICValue22= HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_2);
			// calculate the Duty Cycle
			Duty2 = ((HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_2) *1000000)/(ICValue2*100));

		}
	}
	}
	if (htim == &htim2)
	{
	if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)  // If the interrupt is triggered by channel 1
	{
		// Read the IC value
		ICValue1 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);

		if (ICValue1 != 0)
		{
			ICValue12= HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_2);
			// calculate the Duty Cycle
			Duty1 = ((HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_2) *10000)/(ICValue1));

		}
	}
	if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_3)  // If the interrupt is triggered by channel 1
		{
			// Read the IC value
			ICValue6 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_3);

			if (ICValue6 != 0)
			{
				ICValue62= HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_4);
				// calculate the Duty Cycle
				Duty6 = ((HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_4) *10000)/(ICValue6));

			}
		}
	}
	if (htim == &htim3)
	{
	if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)  // If the interrupt is triggered by channel 1
	{
		// Read the IC value
		ICValue3 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);

		if (ICValue3 != 0)
		{
			ICValue32= HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_2);
			// calculate the Duty Cycle
			Duty3 = ((HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_2) *1000000)/(ICValue3*100));
		}
	}
	}
	if (htim == &htim4)
	{
	if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)  // If the interrupt is triggered by channel 1
	{
		// Read the IC value
		ICValue5 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);

		if (ICValue5 != 0)
		{
			ICValue52= HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_2);
			// calculate the Duty Cycle
			Duty5 = ((HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_2) *1000000)/(ICValue5*100));

		}
	}
	}
	if (htim == &htim8)
	{
	if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)  // If the interrupt is triggered by channel 1
	{
		// Read the IC value
		ICValue4 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);

		if (ICValue4 != 0)
		{
			ICValue42= HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_2);
			// calculate the Duty Cycle
			Duty4 = ((HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_2) *1000000)/(ICValue4*100));

		}
	}
	}
}



void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if(htim == &htim15)
  {
		 uint8_t tx_buffer[64];
		 int resp_len = sprintf((char*)tx_buffer, "%d, %d, %d, %d, %d ,%d\n\r", Duty2, Duty1, Duty6, Duty3, Duty5, Duty4); // Creating a message with RPM, RPM_REF, DUTY to send to termial
		 HAL_UART_Transmit(&huart2, tx_buffer, resp_len, 10);
		 }
}

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

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
  MX_USART2_UART_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  MX_TIM8_Init();
  MX_TIM15_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_IC_Start_IT(&htim1, TIM_CHANNEL_1);   // main channel
  HAL_TIM_IC_Start(&htim1, TIM_CHANNEL_2);   // indirect channel
  HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_1);   // main channel
  HAL_TIM_IC_Start(&htim2, TIM_CHANNEL_2);   // indirect channel
  HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_3);   // main channel
  HAL_TIM_IC_Start(&htim2, TIM_CHANNEL_4);   // indirect channel
  HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_1);   // main channel
  HAL_TIM_IC_Start(&htim3, TIM_CHANNEL_2);   // indirect channel
  HAL_TIM_IC_Start_IT(&htim4, TIM_CHANNEL_1);   // main channel
  HAL_TIM_IC_Start(&htim4, TIM_CHANNEL_2);   // indirect channel
  HAL_TIM_IC_Start_IT(&htim8, TIM_CHANNEL_1);   // main channel
  HAL_TIM_IC_Start(&htim8, TIM_CHANNEL_2);   // indirect channel
  HAL_TIM_Base_Start_IT(&htim15);
  // main channel


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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

  /** Configure the main internal regulator output voltage
  */
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1_BOOST);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV4;
  RCC_OscInitStruct.PLL.PLLN = 85;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
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
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
