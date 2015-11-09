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
#include "systick.h"

#include "FreeRTOS.h"
#include "task.h"

#include <string>
#include <sstream>

volatile int stuff;


void init_system (void);

void test_task (void *)
{
  BSP_LED_Init (LED1);
  TickType_t xLastWakeTime;
  xLastWakeTime = xTaskGetTickCount();
  while (true)
    {
      BSP_LED_Toggle(LED1);
      // Task wird erst in 100 Ticks weiter ausgeführt
      //vTaskDelay ((int)1000/3);
      vTaskDelayUntil (&xLastWakeTime, (TickType_t) 1000/3);
      BSP_LED_Toggle(LED1);
      //vTaskDelay ((int)2000/3);
      vTaskDelayUntil (&xLastWakeTime, (TickType_t) 2000/3);
    }
}

void led1_task (void *)
{
  BSP_LED_Init (LED4);
  TickType_t xLastWakeTime;
  xLastWakeTime = xTaskGetTickCount();
  while (true)
    {
	  stuff = 0;
      BSP_LED_Toggle(LED4);
      // Task wird erst in 100 Ticks weiter ausgeführt
      //vTaskDelay ((int)1000/3);
      for( volatile long int counter = 0;counter<1000000;counter++)
  		;
      BSP_LED_Toggle(LED4);
      //vTaskDelay ((int)2000/3);
      for( volatile long int counter = 0;counter<2000000;counter++)
        ;
      taskYIELD();
    }
}

void led2_task (void *)
{
  BSP_LED_Init (LED3);
  TickType_t xLastWakeTime;
  xLastWakeTime = xTaskGetTickCount();
  while (true)
    {
	  stuff = 0;
      BSP_LED_Toggle(LED3);
      // Task wird erst in 100 Ticks weiter ausgeführt
      //vTaskDelay ((int)1000/3);
      for( volatile long int counter = 0;counter<1000000;counter++)
  		;
      BSP_LED_Toggle(LED3);
      //vTaskDelay ((int)2000/3);
      for( volatile long int counter = 0;counter<2000000;counter++)
        ;
      taskYIELD();
    }
}

void lcd_task (void *)
{
	std::stringstream output;
	std::string outputstring;
	const char * chararray;
	int i = 0;
	for(;;)
	{
		stuff = 0;
		output.str(std::string());
		output << "Counter: " << i%1000;
		outputstring = "";
		outputstring = output.str();
		chararray = "";
		chararray = outputstring.c_str();
		lcd_write_line (1, (char *) chararray);
		for( volatile long int counter = 0;counter<1000000;counter++)
		  		;
		i++;
		taskYIELD();
	}
}

#define LED_TASK_PRIORITY ((1 + tskIDLE_PRIORITY) | portPRIVILEGE_BIT)
#define LCD_TASK_PRIORITY ((1 + tskIDLE_PRIORITY) | portPRIVILEGE_BIT)

/** @brief main function, entry point of the application */
int
main (void)
{
  init_system ();
  HAL_Init ();

  lcd_init ();
  lcd_write_line (0, "Hello FreeRTOS");

  //xTaskCreate( (pdTASK_CODE)test_task, 	"test", configMINIMAL_STACK_SIZE, 0, TEST_TASK_PRIORITY, NULL);
  xTaskCreate( (pdTASK_CODE)led1_task, 	"led1", 256, 0, LED_TASK_PRIORITY, NULL);
  xTaskCreate( (pdTASK_CODE)led2_task, 	"led2", 256, 0, LED_TASK_PRIORITY, NULL);
  xTaskCreate( (pdTASK_CODE)lcd_task, 	"lcd", 256, 0, LCD_TASK_PRIORITY, NULL);

  vTaskStartScheduler ();
}
