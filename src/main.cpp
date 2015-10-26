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
#include <string>
#include <sstream>

#include "lcd.h"
#include "button.h"
#include "systick.h"
#include "timer.h"

bool volatile LED_is_ON;
volatile int mytimer;

/** @brief main function, entry point of the application */
int
main (void)
{
  HAL_Init ();

  SysTick_init ();
  pushbutton_init ();
  BSP_LED_Init (LED1);
  // Test: leuchtet LED3?
  BSP_LED_Init (LED3);
  BSP_LED_On( LED3);
  lcd_init ();
  const char * LCDstring = "HELLO LCD TEST";
  lcd_write_line (0, (char *) LCDstring);
  std::stringstream output;
  std::string outputstring;
  const char * chararray;
  mytimer = 0;
  Timer mytimerobject(12,34,56);


  while (true) // SUPER LOOP
    {
	  if(running)
	  {
		  output.str(std::string());
		  mytimerobject.setMin(mytimer/1000/60);
		  mytimerobject.setSec(mytimer/1000);
		  mytimerobject.setHun(mytimer/10);
		  output << "Time: " << mytimerobject.printtime();
		  outputstring = "";
		  outputstring = output.str();
		  chararray = "";
		  chararray = outputstring.c_str();
		  lcd_write_line (1, (char *) chararray);
	  }
		if( LED_is_ON)
		  BSP_LED_On( LED1);
		else
		  BSP_LED_Off( LED1);
    }
}
