/**
 ******************************************************************************
 * @file    button.cpp
 * @author  Dr. Klaus Schaefer
 * @brief   pushbutton driver
 ******************************************************************************
 */

#include "stm324xg_eval.h"
#include "stm324xg_eval_io.h"

extern bool LED_is_ON;

/** @brief  This function handles External line0 interrupt request from KEY
 *
 * It will be called whenever the button is pressed
 * */
extern "C" void
EXTI15_10_IRQHandler (void)
{
  /* reset both EXTI I/O interrupt latches,
   * as both buttons share the same interrupt
   * and we don't know which one triggered */
  __HAL_GPIO_EXTI_CLEAR_IT( KEY_BUTTON_PIN);
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
  BSP_PB_Init (BUTTON_KEY, BUTTON_MODE_EXTI);
  BSP_PB_Init (BUTTON_WAKEUP, BUTTON_MODE_EXTI);
  BSP_PB_Init (BUTTON_TAMPER, BUTTON_MODE_EXTI);
}
