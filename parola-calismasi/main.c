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


void SystemClock_Config(void);
static void MX_GPIO_Init(void);



int main(void)
{
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();



  int step = 0;
  int btn1 = HAL_GPIO_ReadPin(BUTTON1_GPIO_Port, BUTTON1_Pin);
  int btn2 = HAL_GPIO_ReadPin(BUTTON2_GPIO_Port, BUTTON2_Pin);
  int btn3 = HAL_GPIO_ReadPin(BUTTON3_GPIO_Port, BUTTON3_Pin);
  int password = 12132;
  int passInput = 0;
  while(1){
	  while(passInput != password){
		  while(btn1==SET && btn2==SET && btn3==SET){
			  btn1 = HAL_GPIO_ReadPin(BUTTON1_GPIO_Port, BUTTON1_Pin);
			  btn2 = HAL_GPIO_ReadPin(BUTTON2_GPIO_Port, BUTTON2_Pin);
			  btn3 = HAL_GPIO_ReadPin(BUTTON3_GPIO_Port, BUTTON3_Pin);
		  }
		  if(btn1==RESET)passInput=(passInput*10)+1;
		  else if(btn2==RESET)passInput=(passInput*10)+2;
		  else if(btn3==RESET)passInput=(passInput*10)+3;
		  if(step==0)HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, SET);
		  else if(step==1)HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, SET);
		  else if(step==2)HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, SET);
		  else if(step==3)HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, SET);
		  else if(step==4)HAL_GPIO_WritePin(LED5_GPIO_Port, LED5_Pin, SET);
		  while(btn1==RESET || btn2==RESET || btn3==RESET){
			  btn1=HAL_GPIO_ReadPin(BUTTON1_GPIO_Port, BUTTON1_Pin);
			  btn2=HAL_GPIO_ReadPin(BUTTON2_GPIO_Port, BUTTON2_Pin);
			  btn3=HAL_GPIO_ReadPin(BUTTON3_GPIO_Port, BUTTON3_Pin);
		  }
		  step=(step+1)%5;
		  HAL_GPIO_WritePin(BUZZER_GPIO_Port, BUZZER_Pin, SET);
		  HAL_Delay(50);
		  HAL_GPIO_WritePin(BUZZER_GPIO_Port, BUZZER_Pin, RESET);
		  if(step==0 && passInput>9999){
			  HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, RESET);
			  HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, RESET);
			  HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, RESET);
			  HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, RESET);
			  HAL_GPIO_WritePin(LED5_GPIO_Port, LED5_Pin, RESET);
		  }
		  if(passInput!=password && passInput>9999){
			  passInput=0;
			  HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, SET);
			  HAL_GPIO_WritePin(BUZZER_GPIO_Port, BUZZER_Pin, SET);
			  HAL_Delay(1000);
			  HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, RESET);
			  HAL_GPIO_WritePin(BUZZER_GPIO_Port, BUZZER_Pin, RESET);
		  }
	  }
	  	  HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, SET);
		  HAL_GPIO_WritePin(BUZZER_GPIO_Port, BUZZER_Pin, SET);
		  HAL_Delay(200);
		  HAL_GPIO_WritePin(BUZZER_GPIO_Port, BUZZER_Pin, RESET);
		  HAL_Delay(50);
		  HAL_GPIO_WritePin(BUZZER_GPIO_Port, BUZZER_Pin, SET);
		  HAL_Delay(200);
		  HAL_GPIO_WritePin(BUZZER_GPIO_Port, BUZZER_Pin, RESET);
		  HAL_Delay(50);
		  HAL_GPIO_WritePin(BUZZER_GPIO_Port, BUZZER_Pin, SET);
		  HAL_Delay(200);
		  HAL_GPIO_WritePin(BUZZER_GPIO_Port, BUZZER_Pin, RESET);
		  HAL_Delay(50);
		  HAL_GPIO_WritePin(BUZZER_GPIO_Port, BUZZER_Pin, SET);
		  HAL_Delay(600);
		  HAL_GPIO_WritePin(BUZZER_GPIO_Port, BUZZER_Pin, RESET);
		  HAL_Delay(300);
  }
}

void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};



  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);




  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV1;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}


static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};


  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();


  HAL_GPIO_WritePin(BUZZER_GPIO_Port, BUZZER_Pin, GPIO_PIN_RESET);


  HAL_GPIO_WritePin(LED5_GPIO_Port, LED5_Pin, GPIO_PIN_RESET);


  HAL_GPIO_WritePin(GPIOD, LED4_Pin|LED3_Pin|LED2_Pin|LED1_Pin, GPIO_PIN_RESET);


  GPIO_InitStruct.Pin = BUTTON1_Pin|BUTTON2_Pin|BUTTON3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);


  GPIO_InitStruct.Pin = BUZZER_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(BUZZER_GPIO_Port, &GPIO_InitStruct);


  GPIO_InitStruct.Pin = LED5_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED5_GPIO_Port, &GPIO_InitStruct);


  GPIO_InitStruct.Pin = LED4_Pin|LED3_Pin|LED2_Pin|LED1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);



}





void Error_Handler(void)
{

  __disable_irq();
  while (1)
  {
  }

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
