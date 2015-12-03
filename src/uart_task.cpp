/*
 * uart.cpp
 *
 *  Created on: Nov 16, 2015
 *      Author: schaefer
 */

/* Includes ------------------------------------------------------------------*/
#include "uart.h"
#include "common.h"

#include "FreeRTOS.h"
#include "task.h"

ROM char message[]="hello via UART\r\n";

/** @brief  demo task demonstrating USART usage */
void uart_task( void *)
{
  uint8_t buffer[2]={0};
  uart uart3;

  uart3.puts(message);

  while( true)
    {
	uart3.wait_4_character();
	buffer[0] = uart3.receive();
	uart3.puts( (const char *)buffer);
    }
}
