/**
 * @file    main.cpp
 * @brief   system start code
 * @author  Dr. Klaus Schaefer schaefer@eit.h-da.de
 * @mainpage
 * Sample Projekt for the STM3240G-Eval Evaluation-Board
 */

#include <string.h>
#include "stm324xg_eval.h"
#include "stm324xg_eval_io.h"
#include "stm324xg_eval_ts.h"
#include "stm324xg_eval_lcd.h"

#include "stm32f4xx_hal.h"

#include "lcd.h"
#include "button.h"

#include "FreeRTOS.h"
#include "task.h"

#include "common.h"
#include "candriver.h"

void init_system (void);
void uart_task( void *);
void bargraph_task( void *);
void pushbutton_task(void *);
void init_FreeRTOS_reporting( void);
void scope_task (void *);

void test_task1 (void *)
{
  BSP_LED_Init (LED1);
  while (true)
    {
	  oszi_trigger();
	  BSP_LED_Toggle(LED1);
      vTaskDelay (100);
	  oszi_trigger();
      BSP_LED_Toggle(LED1);
      vTaskDelay (400);
    }
}

void test_task2 (void *)
{
  BSP_LED_Init (LED2);
  while (true)
    {
	  oszi_trigger();
	  BSP_LED_Toggle(LED2);
      vTaskDelay (100);
	  oszi_trigger();
      BSP_LED_Toggle(LED2);
      vTaskDelay (400);
    }
}

void test_task3 (void *)
{
  BSP_LED_Init (LED3);
  while (true)
    {
	  oszi_trigger();
	  BSP_LED_Toggle(LED3);
      vTaskDelay (100);
	  oszi_trigger();
      BSP_LED_Toggle(LED3);
      vTaskDelay (400);
    }
}

COMMON can_driver_t *can;

void can_receive_task (void *)
{
	can_driver_t::CANpacket rxcanpk;
	char canpkchar[] = {0,0};
	while(true)
	{
		can->receive(rxcanpk);

		BSP_LCD_ClearStringLine(1);
		lcd_write_line(1, (char *) rxcanpk.data_b);
	}
}

#define TEST_TASK_PRIORITY (tskIDLE_PRIORITY | portPRIVILEGE_BIT)



/** @brief main function, entry point of the application */
void main (void)
{
  init_system ();
  HAL_Init ();

  lcd_init ();
  lcd_write_line (0, "Hello FreeRTOS");

  init_FreeRTOS_reporting ();

  xTaskCreate( (pdTASK_CODE)test_task1, 	"test1", configMINIMAL_STACK_SIZE, 0, TEST_TASK_PRIORITY+4, NULL);
  xTaskCreate( (pdTASK_CODE)test_task2, 	"test2", configMINIMAL_STACK_SIZE, 0, TEST_TASK_PRIORITY+6, NULL);
  xTaskCreate( (pdTASK_CODE)test_task3, 	"test3", configMINIMAL_STACK_SIZE, 0, TEST_TASK_PRIORITY+8, NULL);
  //xTaskCreate( (pdTASK_CODE)bargraph_task, 	"bar",   configMINIMAL_STACK_SIZE, 0, TEST_TASK_PRIORITY+2, NULL);
  //xTaskCreate( (pdTASK_CODE)scope_task,		"scope" ,configMINIMAL_STACK_SIZE+128, 0, TEST_TASK_PRIORITY+7, NULL);
  xTaskCreate( (pdTASK_CODE)uart_task, 		"uart",  configMINIMAL_STACK_SIZE, 0, TEST_TASK_PRIORITY+7, NULL);
  xTaskCreate( (pdTASK_CODE)pushbutton_task,	"button",configMINIMAL_STACK_SIZE+128, 0, TEST_TASK_PRIORITY+7, NULL);

  can = new can_driver_t( 3);

  xTaskCreate( (pdTASK_CODE)can_receive_task, 		"uart",  configMINIMAL_STACK_SIZE, 0, TEST_TASK_PRIORITY+7, NULL);

  vTaskStartScheduler ();
}
