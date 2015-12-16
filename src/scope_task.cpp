/*************************************************************************
 * @file	scope_task.c
 * @brief
 * @author	Dr. Klaus Schaefer
 **************************************************************************/

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "common.h"
#include "stm324xg_eval_lcd.h"
#include "adc.h"
#include "ring_buffer.h"

#pragma GCC diagnostic ignored "-Wconversion"

// LCD dimensions
#define HEIGHT 	240
#define WIDTH 	320

#define MAP( x) (HEIGHT - (((x)*HEIGHT)>>16))

static RingBuffer<WIDTH, uint32_t> data;

void scope_task (void *);
void scope_task (void *)
{
  int i;
  uint32_t value = 0;
  adc the_adc;

  BSP_LCD_Init ();

  portTickType xLastWakeTime = xTaskGetTickCount ();
  while (true)
    {
      vTaskDelayUntil (&xLastWakeTime, 20);

      // digital filter and scaling for ADC input
      value -= value >> 2;
      value = value + (the_adc.get_value() << 2);

      // update
      data.pushValue (MAP(value));

      // Set the LCD Back Color
  	BSP_LCD_SetBackColor(LCD_COLOR_YELLOW);

      // Set the LCD Text Color


      for (i = 0; i < WIDTH-1; ++i)
	{
	  // erase
	  BSP_LCD_SetTextColor( LCD_COLOR_YELLOW);
	  BSP_LCD_DrawLine( WIDTH - i - 1, data.getValueAt (i - 1), WIDTH - i - 2, data.getValueAt (i));
	  //draw
	  BSP_LCD_SetTextColor( LCD_COLOR_BLUE);
	  BSP_LCD_DrawLine( WIDTH - i - 1, data.getValueAt (i), WIDTH - i - 2, data.getValueAt (i + 1));
	}
      // draw grid
      BSP_LCD_SetTextColor( LCD_COLOR_BLACK);
      for (i = 0; i < WIDTH; i += WIDTH / 8)
	BSP_LCD_DrawLine(i, 0, i, HEIGHT);

      for (i = 0; i < HEIGHT; i += HEIGHT / 6)
	BSP_LCD_DrawLine(0, i, WIDTH, i);
    }
}
