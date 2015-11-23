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
// #include "semphr.h"
// #include "queue.h"
// #include <string>
// #include <sstream>

#include "lcd.h"
#include "button.h"

#include "FreeRTOS.h"
#include "task.h"

void init_system (void);
void bargraph_task(void *);
// void laufschrift_task(void *);
void uart_task( void *);
void test_task (void *);
// void lcd_balkenanzeige (void *);
// void lcd_laufschrift (void *);
// void lcd_zeit (void *);
void main (void);

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

/*void lcd_balkenanzeige (void *)
{

	static std::stringstream output;
	static std::string outputstring;
	static const char * chararray;
	static int i = 0;
	static int direction = 1;
	static char test[] = "123456789ABCDE";
	char first;
	while(true)
	{
		if( xSemaphoreMutex != NULL )
		{
			xSemaphoreTake( xSemaphoreMutex, ( TickType_t ) 0 )
		}
		for(int j = 0;j<(int) strlen(test);j++)
		{
			if (j == 0)
				first = test[0];
			if(j < (int)strlen(test)-1)
				test[j] = test[j+1];
			if (j == (int)strlen(test)-1)
				test[j]=first;

		}
		BSP_LCD_SetTextColor(LCD_COLOR_GREEN);
		BSP_LCD_FillRect(0, 0, 240, 24);
		BSP_LCD_SetTextColor(LCD_COLOR_RED);
		if(direction==1)
			BSP_LCD_FillRect(i, 0, 100, 24);
					BSP_LCD_FillRect(i, 0, 100, 24);
		for( volatile long int counter = 0;counter<1000000;counter++)
		  		;
		if(direction == 1)
			i++;
		else
			i--;
		if(i == 140 || i == 0)
		{
			direction++;
			direction = direction %2;
		}
		if( xSemaphoreMutex != NULL )
		{
			xSemaphoreGive( xSemaphoreMutex );
		}
	}
}

void lcd_laufschrift (void *)
{

	static std::stringstream output;
	static std::string outputstring;
	static const char * chararray;
	static char test[] = "123456789ABCDE";
	char first;
	while(true)
	{
		if( xSemaphoreMutex != NULL )
		{
			xSemaphoreTake( xSemaphoreMutex, ( TickType_t ) 0 )
		}
		for(int j = 0;j<(int) strlen(test);j++)
		{
			if (j == 0)
				first = test[0];
			if(j < (int)strlen(test)-1)
				test[j] = test[j+1];
			if (j == (int)strlen(test)-1)
				test[j]=first;

		}
		BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
		BSP_LCD_SetTextColor(LCD_COLOR_YELLOW);
		BSP_LCD_DisplayStringAtLine (1, (uint8_t *) &test);
		for( volatile long int counter = 0;counter<1000000;counter++)
		  		;
		if( xSemaphoreMutex != NULL )
		{
			xSemaphoreGive( xSemaphoreMutex );
		}
	}
}

void lcd_zeit (void *)
{

	static std::stringstream output;
	static std::string outputstring;
	static const char * chararray;
	static int i = 0;
	static Timer mytimerobject(12,34,56);

	while(1)
	{
		if( xSemaphoreMutex != NULL )
		{
			xSemaphoreTake( xSemaphoreMutex, ( TickType_t ) 0 )
		}
		output.str(std::string());
		mytimerobject.setMin(systick_count/1000/60);
		mytimerobject.setSec(systick_count/1000);
		mytimerobject.setHun(systick_count/10);
		output << "Time " << mytimerobject.printtime();
		outputstring = "";
		outputstring = output.str();
		chararray = "";
		chararray = outputstring.c_str();
		BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
		BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
		BSP_LCD_DisplayStringAtLine (2, (uint8_t *) chararray);
		i++;
		if( xSemaphoreMutex != NULL )
		{
			xSemaphoreGive( xSemaphoreMutex );
		}
	}

}*/

#define TASK_PRIORITY (1 | portPRIVILEGE_BIT)
TaskHandle_t LCDTaskHandle;
// SemaphoreHandle_t xSemaphore = NULL;
// QueueHandle_t xQueue;
// SemaphoreHandle_t xSemaphoreMutex;

/** @brief main function, entry point of the application */
void main (void)
{
  init_system ();
  HAL_Init ();

  // xSemaphore = xSemaphoreCreateBinary();
  // xQueue = xQueueCreate( 15, sizeof( char *) );

  xTaskCreate( (pdTASK_CODE)uart_task, 	   "uart",     configMINIMAL_STACK_SIZE, 0, TASK_PRIORITY, NULL);

  xTaskCreate( (pdTASK_CODE)test_task, 	   "test",     configMINIMAL_STACK_SIZE, 0, TASK_PRIORITY, NULL);

  xTaskCreate( (pdTASK_CODE)bargraph_task, "bargraph", configMINIMAL_STACK_SIZE, 0, TASK_PRIORITY, &LCDTaskHandle);

  xTaskCreate( (pdTASK_CODE)pushbutton_task, "button", configMINIMAL_STACK_SIZE, 0, TASK_PRIORITY, NULL);

  // xTaskCreate( (pdTASK_CODE)laufschrift_task, 	   "laufschrift",     configMINIMAL_STACK_SIZE, 0, TASK_PRIORITY, NULL);

  //xTaskCreate( (pdTASK_CODE)lcd_balkenanzeige, "button", configMINIMAL_STACK_SIZE, 0, TASK_PRIORITY, NULL);
  //xTaskCreate( (pdTASK_CODE)lcd_laufschrift, "button", configMINIMAL_STACK_SIZE, 0, TASK_PRIORITY, NULL);
  //xTaskCreate( (pdTASK_CODE)lcd_zeit, "button", configMINIMAL_STACK_SIZE, 0, TASK_PRIORITY, NULL);

  vTaskStartScheduler ();
}
