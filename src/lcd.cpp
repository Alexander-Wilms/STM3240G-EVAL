/**
 * @file        lcd.cpp
 * @brief       simple LCD driver module
 */

#include "stm324xg_eval_lcd.h"

#include "FreeRTOS.h"
#include "task.h"

#include <string.h>
#include <string>
#include <sstream>

volatile uint16_t TextColor, BackColor; // globals needed by LCD driver

// extern TaskHandle_t LCDTaskHandle;
// extern QueueHandle_t xQueue;

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
		//	if( xSemaphore != NULL )
		//	{
		//		if( xSemaphoreTake( xSemaphore, ( TickType_t ) 10 ) == pdTRUE )
		//		{

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
		vTaskDelay(333);

		// }}

		// bargraph_task suspendieren
		// vTaskSuspend(0);
	}
}

void laufschrift_task (void *)
{
	static std::stringstream output;
	static std::string outputstring;
	static const char * chararray;
	static char test[] = "";
	char first;
	static int i = 0;
	while(true)
	{
		/*if( xQueue != 0 )
		{
			xQueueReceive( xQueue, &( test[i] ), ( TickType_t ) 10 );
			i++;
			i = i%15;
		}*/
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
	}
}
