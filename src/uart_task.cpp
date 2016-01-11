/*
 * uart.cpp
 *
 *  Created on: Nov 16, 2015
 *      Author: schaefer
 */

/* Includes ------------------------------------------------------------------*/
#include "uart.h"
#include "common.h"
#include "lcd.h"

#include "stm324xg_eval_lcd.h"

#include "FreeRTOS.h"
#include "task.h"

ROM char message[]="hello via UARTb\r\n";

/** @brief  demo task demonstrating USART usage */
void uart_task( void *)
{
	char output[2] = {0, 0};
  char buffer[30]={0};
  uart uart3;

  uart3.puts(message);

  int i = 0;

  while( true)
    {
		while(i < 30)
		{
			uart3.wait_4_character();
			buffer[i] = uart3.receive();
			output[0] = buffer[i];
			uart3.puts( (const char *)output);
			if(buffer[i] == '\r')  break;
			i++;
		}
		output[0] = '\n';
		uart3.puts( (const char *)output);
		buffer[i]=0;

		BSP_LCD_ClearStringLine(1);
		lcd_write_line(1, buffer);
		i = 0;
    }
}
