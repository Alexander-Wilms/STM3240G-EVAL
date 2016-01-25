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
#include "timer.h"

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "systick.h"

#include <string>
#include <sstream>
#include <iomanip>
using namespace std;

#include "common.h"

void init_system (void);
void uart_task( void *);
void bargraph_task( void *);
void pushbutton_task(void *);
void init_FreeRTOS_reporting( void);

TaskHandle_t TaskHandle;
SemaphoreHandle_t xSemaphoreMutex;
volatile int systick_count;

void test_task1 (void *)
{
  BSP_LED_Init (LED1);
  while (true)
    {
	  oszi_trigger();
	  BSP_LED_Toggle(LED1);
      //vTaskDelay (100);
	  for(int i=0;i<50000;i++)
		  ;
	  //oszi_trigger();
      BSP_LED_Toggle(LED1);
      //vTaskDelay (400);
      vTaskSuspend(0);
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

void lcd_zeit (void *)
{
	BSP_LED_Init (LED3);
	static std::stringstream output;
	static std::string outputstring;
	static const char * chararray;
	static Timer mytimerobject(12,34,56,78);
	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	while(true)
	{
		BSP_LED_Toggle(LED3);
		output.str(std::string());
		mytimerobject.setStu(systick_count/1000/60/60);
		mytimerobject.setMin(systick_count/1000/60);
		mytimerobject.setSec(systick_count/1000);
		output << "Time " << std::setfill('0') << std::setw(2) << mytimerobject.getStu() << ":" <<  std::setfill('0') << std::setw(2) << mytimerobject.getMin() << ":" << std::setfill('0') << std::setw(2) << mytimerobject.getSec();
		//output << "Time " << mytimerobject.printtime();
		outputstring = "";
		outputstring = output.str();
		chararray = "";
		chararray = outputstring.c_str();
		if( xSemaphoreMutex != NULL )
		{
			if( xSemaphoreTake( xSemaphoreMutex, ( TickType_t ) 0 ) == pdTRUE )
			{
				BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
				BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
				BSP_LCD_DisplayStringAtLine (6, (uint8_t *) chararray);
				xSemaphoreGive( xSemaphoreMutex );
			}
		}
		vTaskDelay (100);
	}
}

#define TEST_TASK_PRIORITY (tskIDLE_PRIORITY | portPRIVILEGE_BIT)


/** @brief main function, entry point of the application */
int main (void)
{
  init_system ();
  HAL_Init ();

  lcd_init ();
  lcd_write_line (0, "Hello FreeRTOS");

  init_FreeRTOS_reporting ();
  xSemaphoreMutex = xSemaphoreCreateMutex();

  xTaskCreate( (pdTASK_CODE)test_task1, 	"test", configMINIMAL_STACK_SIZE, 0, TEST_TASK_PRIORITY+4, &TaskHandle);
  //xTaskCreate( (pdTASK_CODE)test_task2, 	"test", configMINIMAL_STACK_SIZE, 0, TEST_TASK_PRIORITY+6, NULL);
  //xTaskCreate( (pdTASK_CODE)test_task3, 	"test", configMINIMAL_STACK_SIZE, 0, TEST_TASK_PRIORITY+8, NULL);
  xTaskCreate( (pdTASK_CODE)bargraph_task, 	"test", configMINIMAL_STACK_SIZE, 0, TEST_TASK_PRIORITY+2, NULL);
  // xTaskCreate( (pdTASK_CODE)uart_task, 		"test", configMINIMAL_STACK_SIZE, 0, TEST_TASK_PRIORITY+7, NULL);
  // xTaskCreate( (pdTASK_CODE)pushbutton_task, 		"test", configMINIMAL_STACK_SIZE, 0, TEST_TASK_PRIORITY+7, NULL);
  //xTaskCreate( (pdTASK_CODE)lcd_zeit, 		"test", configMINIMAL_STACK_SIZE, 0, TEST_TASK_PRIORITY+3, NULL);

  vTaskStartScheduler ();
}
