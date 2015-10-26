/**
 ******************************************************************************
 * @file    button.cpp
 * @author  Dr. Klaus Schaefer
 * @brief   pushbutton driver
 ******************************************************************************
 */

#include "stm324xg_eval.h"
#include "stm324xg_eval_io.h"

extern volatile bool LED_is_ON;
volatile int count;
volatile bool running = true;

/** @brief  This function handles External line0 interrupt request from KEY
 *
 * It will be called whenever the button is pressed
 * */
extern "C" void
EXTI15_10_IRQHandler (void)
{
	count = 50;
  /* reset both EXTI I/O interrupt latches,
   * as both buttons share the same interrupt
   * and we don't know which one triggered */
  __HAL_GPIO_EXTI_CLEAR_IT( KEY_BUTTON_PIN);
  // Disable interrupts
  BSP_PB_Init (BUTTON_KEY, BUTTON_MODE_GPIO);
  // Toggle state
  running = !running;
  // Show status
  BSP_LED_On( LED2);
  // Toggle LED
  LED_is_ON = ! LED_is_ON;
}

/** @brief  This function handles interrupt requests from TAMPER AND WAKEUP
 *
 * It will be called whenever TAMPER or WAKEUP is pressed
 * */
extern "C" void
EXTI0_IRQHandler (void)
{
  /* reset EXTI I/O interrupt latch */
  __HAL_GPIO_EXTI_CLEAR_IT(WAKEUP_BUTTON_PIN);
}

/** @brief button interrupt initialization */
void
pushbutton_init (void)
{
  /* Initialize USER Buttons with interrupt capability */
	// Drücken führt zu Interrupt
  BSP_PB_Init (BUTTON_KEY, BUTTON_MODE_EXTI);
  BSP_PB_Init (BUTTON_WAKEUP, BUTTON_MODE_EXTI);
  BSP_PB_Init (BUTTON_TAMPER, BUTTON_MODE_EXTI);
}
