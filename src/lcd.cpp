/**
 * @file        lcd.cpp
 * @brief       simple LCD driver module
 */

#include "stm324xg_eval_lcd.h"

#include "FreeRTOS.h"
#include "task.h"

volatile uint16_t TextColor, BackColor; // globals needed by LCD driver

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
	  oszi_trigger();
	  TickType_t xLastWakeTime;
      for (uint16_t width = 0; width < 320; ++width)
	{
    	  oszi_trigger();
	  BSP_LCD_SetTextColor(LCD_COLOR_RED);
	  BSP_LCD_DrawFullRect (0, 50, width, 10);
	  BSP_LCD_SetTextColor(LCD_COLOR_YELLOW);
	  BSP_LCD_DrawFullRect (width, 50, 320 - width - 1, 10);
	  oszi_trigger();
	  xLastWakeTime = xTaskGetTickCount();
	  vTaskDelayUntil (&xLastWakeTime, (TickType_t) 10);
	  oszi_trigger();

	}
      for (uint16_t width = 319; width > 0; --width)
	{
    	  oszi_trigger();
	  BSP_LCD_SetTextColor(LCD_COLOR_RED);
	  BSP_LCD_DrawFullRect (0, 50, width, 10);
	  BSP_LCD_SetTextColor(LCD_COLOR_YELLOW);
	  BSP_LCD_DrawFullRect (width, 50, 320 - width - 1, 10);
	  oszi_trigger();
	  xLastWakeTime = xTaskGetTickCount();
	  vTaskDelayUntil (&xLastWakeTime, (TickType_t) 10);
	  oszi_trigger();
	}
      oszi_trigger();

    }
}
