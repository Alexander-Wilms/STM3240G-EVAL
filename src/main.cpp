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

bool LED_is_ON;

/** @brief main function, entry point of the application */
int
main (void)
{
  HAL_Init ();

  SysTick_init ();
  pushbutton_init ();
  BSP_LED_Init (LED1);
  lcd_init ();
  lcd_write_line (0, "Hello LCD");

  while (true) // SUPER LOOP
    {
	if( LED_is_ON)
	  BSP_LED_On( LED1);
	else
	  BSP_LED_Off( LED1);
    }
}
