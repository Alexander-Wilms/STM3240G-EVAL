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

#include "lcd.h"
#include "button.h"

#include "FreeRTOS.h"
#include "task.h"

void init_system (void);
void bargraph_task(void *);
void uart_task( void *);

void test_task (void *)
{
  BSP_LED_Init (LED1);
  while (true)
    {
      BSP_LED_Toggle(LED1);
      vTaskDelay (configTICK_RATE_HZ/10);
      BSP_LED_Toggle(LED1);
      vTaskDelay (9*configTICK_RATE_HZ/10);
    }
}

#define TASK_PRIORITY (1 | portPRIVILEGE_BIT)

/** @brief main function, entry point of the application */
void main (void)
{
  init_system ();
  HAL_Init ();

  xTaskCreate( (pdTASK_CODE)uart_task, 	   "uart",     configMINIMAL_STACK_SIZE, 0, TASK_PRIORITY, NULL);
  xTaskCreate( (pdTASK_CODE)test_task, 	   "test",     configMINIMAL_STACK_SIZE, 0, TASK_PRIORITY, NULL);
  xTaskCreate( (pdTASK_CODE)bargraph_task, "bargraph", configMINIMAL_STACK_SIZE, 0, TASK_PRIORITY, NULL);
  xTaskCreate( (pdTASK_CODE)pushbutton_task, "button", configMINIMAL_STACK_SIZE, 0, TASK_PRIORITY, NULL);

  vTaskStartScheduler ();
}
