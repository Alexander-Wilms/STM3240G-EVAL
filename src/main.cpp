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

#include "FreeRTOS.h"
#include "task.h"

void init_system (void);

void test_task (void *)
{
  BSP_LED_Init (LED1);
  while (true)
    {
      BSP_LED_Toggle(LED1);
      // Task wird erst in 100 Ticks weiter ausgeführt
      vTaskDelay ((int)1000/3);
      BSP_LED_Toggle(LED1);
      vTaskDelay ((int)2000/3);
    }
}

#define TEST_TASK_PRIORITY ((1 + tskIDLE_PRIORITY) | portPRIVILEGE_BIT)

/** @brief main function, entry point of the application */
int
main (void)
{
  init_system ();
  HAL_Init ();

  lcd_init ();
  lcd_write_line (0, "Hello FreeRTOS");

  xTaskCreate( (pdTASK_CODE)test_task, 	"test", configMINIMAL_STACK_SIZE, 0, TEST_TASK_PRIORITY, NULL);

  vTaskStartScheduler ();
}
