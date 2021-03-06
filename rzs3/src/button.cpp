/**
  ******************************************************************************
 * @file    button.cpp
 * @author  Dr. Klaus Schaefer
 * @brief   pushbutton handler
 ******************************************************************************
 */

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "common.h"
#include "stm324xg_eval.h"

COMMON QueueHandle_t EXTIqueue;
COMMON TimerHandle_t de_bounce_timer;

/** @brief  This function handles External line0 interrupt request. */
extern "C" void
EXTI15_10_IRQHandler(void)
{
  ENTER_ISR;
  portBASE_TYPE TaskWoken = pdFALSE;

  /* reset both EXTI I/O interrupt latches,
   * as both buttons share the same interrupt
   * and we don't know which one triggered */
  __HAL_GPIO_EXTI_CLEAR_IT( KEY_BUTTON_PIN);

  /* disable further interrupts for a while */
  BSP_PB_Init (BUTTON_KEY, BUTTON_MODE_GPIO);

  /* trigger timer callback */
  xTimerStartFromISR(de_bounce_timer, &TaskWoken);

  /* wake up task */
  xQueueSendFromISR( EXTIqueue, 0, &TaskWoken);

  /* preempt the active task if necessary */
  portEND_SWITCHING_ISR(TaskWoken);
}

/** @brief  This function enables the button interrupt 
 * 
 * The interrupt is re-enabled after waiting for a possible bouncing phase.
 * */
void de_bounce_callback(xTimerHandle)
{
  // once more: reset EXTI I/O interrupt latch
  __HAL_GPIO_EXTI_CLEAR_IT( KEY_BUTTON_PIN);
  BSP_PB_Init (BUTTON_KEY, BUTTON_MODE_EXTI);
}

/** @brief  Task function responsible for LED blinking on pushbutton command */
void pushbutton_task(void *)
{
  /* Initialize queue */
  EXTIqueue = xQueueCreate( 10, 0); // actually a counting semaphore
  ASSERT( EXTIqueue != 0);

  /* Initialize timer */
  de_bounce_timer = xTimerCreate(0, 150, 0, 0, de_bounce_callback);
  ASSERT( de_bounce_timer != 0);

  /* Initialize our LED */
  BSP_LED_Init (LED4);

  /* Initialize queue */
  EXTIqueue = xQueueCreate( 10, 0); // actually a counting semaphore
  ASSERT( EXTIqueue != 0);

  /* Initialize USER Button with interrupt capability */
  BSP_PB_Init (BUTTON_KEY, BUTTON_MODE_EXTI);

  for (;;)
    {
      /* Indefinitely wait for pushbutton message */
      xQueueReceive(EXTIqueue, 0, portMAX_DELAY);

      /* blink once */
      BSP_LED_On(LED4);
      vTaskDelay(configTICK_RATE_HZ / 3);
      BSP_LED_Off(LED4);
      vTaskDelay(configTICK_RATE_HZ);
    }
}
