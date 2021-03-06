/**
 * @file        lcd.cpp
 * @brief       simple LCD driver module
 */

#include "stm324xg_eval_lcd.h"

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#include <string.h>
#include <string>
#include <sstream>

volatile uint16_t TextColor, BackColor; // globals needed by LCD driver

extern TaskHandle_t LCDTaskHandle;
extern SemaphoreHandle_t xSemaphore;
extern QueueHandle_t xQueue;

/** @brief LCD initialization
 *
 * needs to be once called before theLCD screen can be used
 *  */
void lcd_init( void)
{
  /* Initialize the LCD */
	BSP_LCD_Init();

    /* Clear the LCD */
	BSP_LCD_Clear(LCD_COLOR_YELLOW);

    /* Set the LCD Back Color */
	BSP_LCD_SetBackColor(LCD_COLOR_YELLOW);

    /* Set the LCD Text Color */
	BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
}

/** @brief write a single line of text on the LCD */
void lcd_write_line( unsigned line, char * text)
{
	BSP_LCD_DisplayStringAtLine( LINE(line), (uint8_t *)text);
}

void
bargraph_task (void *)
{
	lcd_init ();

	lcd_write_line (0, "Hello FreeRTOS");

	while (true)
	{
		/*if( xSemaphore != NULL )
		{
			if( xSemaphoreTake( xSemaphore, ( TickType_t ) 10 ) == pdTRUE )
			{*/
				for (uint16_t width = 0; width < 320; ++width)
				{
					BSP_LCD_SetTextColor(LCD_COLOR_RED);
					BSP_LCD_DrawFullRect (0, 50, width, 10);
					BSP_LCD_SetTextColor(LCD_COLOR_YELLOW);
					BSP_LCD_DrawFullRect (width, 50, 320 - width - 1, 10);
					vTaskDelay (1);
				}
				for (uint16_t width = 319; width > 0; --width)
				{
					BSP_LCD_SetTextColor(LCD_COLOR_RED);
					BSP_LCD_DrawFullRect (0, 50, width, 10);
					BSP_LCD_SetTextColor(LCD_COLOR_YELLOW);
					BSP_LCD_DrawFullRect (width, 50, 320 - width - 1, 10);
					vTaskDelay (1);
				}
				// vTaskDelay(333);
			//}
		//}

		// bargraph_task suspendieren
		// vTaskSuspend(0);
	}
}

void laufschrift_task (void *)
{
	lcd_init ();
	static std::stringstream output;
	static std::string outputstring;
	static const char * chararray;
	static char test[] = "0123456789ABCDE";
	static char outputstuff[] = "0123456789ABCDE";
	char first;
	static int i = 0;
	static int k = 0;
	static int a = 0;
	static int b = 0;
	static int done = 0;
	while(true)
	{

		if( xQueue != 0 )
		{
			if( xQueueReceive( xQueue, &( test[i] ), ( TickType_t ) 10 ) )
			{
				// pcRxedMessage now points to the struct AMessage variable posted
				// by vATask.

				i++;
				i = i%15;
				test[i] = ' ';
			}
		}

		/*done = 0;
		for(int l=0; l<15; l++)
		{
			if(test[l]!= '\0' && done != 1)
			{
				outputstuff[l] = test[l];
			} else
				done = 1;
		}

		for(int m = 1; m < a; m++)
		{
			for(int j = 0;j<(int) strlen(test);j++)
			{
				if (j == 0)
					first = outputstuff[0];
				if(j < (int)strlen(outputstuff)-1)
					outputstuff[j] = outputstuff[j+1];
				if (j == (int)strlen(outputstuff)-1)
					outputstuff[j]=first;
			}
		}
		a++;*/


		BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
		BSP_LCD_SetTextColor(LCD_COLOR_YELLOW);
		BSP_LCD_DisplayStringAtLine (3, (uint8_t *) &test);
		for( volatile long int counter = 0;counter<2000000;counter++)
			;
	}
}
