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

#include "candriver.h"

ROM char message[]="hello via UART\r\n";

uart uart3;

extern COMMON can_driver_t *can;

/** @brief  demo task demonstrating USART usage */
void uart_task( void *)
{
	char output[2] = {0, 0};
	char buffer[30]={0};

	can_driver_t::CANpacket txcanpk;
	uint8_t tx[8] = "ABCDEFG";
	for(int i = 0; i <=8;i++)
	{
		txcanpk.data_b[i] =  tx[i];
	}

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
		buffer[i]=0;

		BSP_LCD_ClearStringLine(1);
		lcd_write_line(1, buffer);
		can->send(txcanpk);
		i = 0;
	}
}
