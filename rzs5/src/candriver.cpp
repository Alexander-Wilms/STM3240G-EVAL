/*
 * candriver.cpp
 *
 *  Created on: Dec 11, 2015
 *      Author: schaefer
 */

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "common.h"
#include "portmacro.h"

#include "candriver.h"
#include "task_builder.h"

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_can.h"
#include "stm32f4xx_hal_cortex.h"

#define CANx                            CAN2
#define CANx_CLK_ENABLE()               __HAL_RCC_CAN2_CLK_ENABLE()
#define CANx_GPIO_CLK_ENABLE()          __HAL_RCC_GPIOB_CLK_ENABLE()

#define CANx_FORCE_RESET()              __HAL_RCC_CAN2_FORCE_RESET()
#define CANx_RELEASE_RESET()            __HAL_RCC_CAN2_RELEASE_RESET()

#define CANx_TX_PIN                    GPIO_PIN_13
#define CANx_TX_GPIO_PORT              GPIOB
#define CANx_TX_AF                     GPIO_AF9_CAN2
#define CANx_RX_PIN                    GPIO_PIN_5
#define CANx_RX_GPIO_PORT              GPIOB
#define CANx_RX_AF                     GPIO_AF9_CAN2

static COMMON can_driver_t *can_driver; //!< singleton CAN driver object

static ROM can_driver_t::CANpacket message=
    {
	2047,		// identifier
	8,		// DLC length
	"1234567"	// data
      };

void can_driver_t::run(void *)
{
  CANpacket msg;

  while (true) // wait for message to send
    {
      can_driver->send( message);
      vTaskDelay(1000);
    }
}

bool can_driver_t::send_can_packet( const CANpacket &msg)
{
  uint8_t transmitmailbox;
  ASSERT(msg.id != 0x123);
  /* Select one empty transmit mailbox */
  if ((CAN2->TSR & CAN_TSR_TME0) == CAN_TSR_TME0)
      transmitmailbox = 0;
  else if ((CAN2->TSR & CAN_TSR_TME1) == CAN_TSR_TME1)
      transmitmailbox = 1;
  else if ((CAN2->TSR & CAN_TSR_TME2) == CAN_TSR_TME2)
      transmitmailbox = 2;
  else
      return false; // give up, no mailbox empty

  /* Set up the Id */
  CAN2->sTxMailBox[transmitmailbox].TIR &= CAN_TI0R_TXRQ;
  CAN2->sTxMailBox[transmitmailbox].TIR |= msg.id << 21;

  /* Set up the DLC */
  CAN2->sTxMailBox[transmitmailbox].TDTR &= (uint32_t) 0xFFFFFFF0;
  CAN2->sTxMailBox[transmitmailbox].TDTR |= msg.dlc;

  /* Set up the data field */
  CAN2->sTxMailBox[transmitmailbox].TDLR = msg.data_w[0];
  CAN2->sTxMailBox[transmitmailbox].TDHR = msg.data_w[1];

  /* Request transmission */
  CAN2->sTxMailBox[transmitmailbox].TIR |= CAN_TI0R_TXRQ;
}

namespace CAN_driver_ISR
{
/**
  * @brief  This function handles CAN2 RX0 interrupt request.
  * @param  None
  * @retval None
  */
extern "C" void CAN2_RX0_IRQHandler(void)
{
  ENTER_ISR;

  can_driver_t::CANpacket msg;

  msg.id = (uint32_t)0x000007FF & (CAN2->sFIFOMailBox[CAN_FIFO0].RIR >> 21);
  msg.dlc= (uint8_t)0x0F & CAN2->sFIFOMailBox[CAN_FIFO0].RDTR;
  msg.data_w[0] = CAN2->sFIFOMailBox[CAN_FIFO0].RDLR;
  msg.data_w[1] = CAN2->sFIFOMailBox[CAN_FIFO0].RDHR;

  BaseType_t xHigherPriorityTaskWoken=false;
  bool result = xQueueSendFromISR( can_driver->RX_queue, &msg, &xHigherPriorityTaskWoken);
  ASSERT( result == true);

  CAN2->RF0R |= CAN_RF0R_RFOM0; // release FIFO 0

  portEND_SWITCHING_ISR( xHigherPriorityTaskWoken);
}

extern "C" void CAN2_TX_IRQHandler(void)
{
  ENTER_ISR;

  can_driver_t::CANpacket msg;
  BaseType_t xHigherPriorityTaskWoken = false;
  if( xQueueReceiveFromISR (can_driver->TX_queue, &msg,
			&xHigherPriorityTaskWoken) == pdTRUE)
    can_driver->send_can_packet( msg);
  else
    CAN2->IER &= ~CAN_IT_TME; // interrupt off, no more work to do

  portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);
}

} // namespace C

static ROM TaskParameters_t task_parameter =
  {
      0, 			// code to be executed
      "can",			// name
      128,			// stack size in 32bit words
      (void *) 0, 		// pointer to the data being passed to the code
      0,		 	// priority
      (uint32_t*) 0,		// dummy stack buffer: will be allocated dynamically
	{
	// memory sections:
	// Base-address Length Parameters
	      { COMMON_BLOCK, COMMON_SIZE, portMPU_REGION_READ_WRITE },
	      { 0, 0, 0 },
	      { 0, 0, 0 }
	}
  };

can_driver_t::can_driver_t (uint8_t priority)
{
  ASSERT( can_driver ==0); 	// this is a singleton class,
  can_driver = this;		// make sure there is only one instance

  __HAL_RCC_CAN1_CLK_ENABLE();  // also required for CAN2 !!
  __HAL_RCC_CAN2_CLK_ENABLE();

  GPIO_InitTypeDef   GPIO_InitStruct;

  /* Enable GPIO clock ****************************************/
  CANx_GPIO_CLK_ENABLE();

  /* Configure peripheral GPIO ##########################################*/
  /* CAN1 TX GPIO pin configuration */
  GPIO_InitStruct.Pin = CANx_TX_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Alternate =  CANx_TX_AF;

  HAL_GPIO_Init(CANx_TX_GPIO_PORT, &GPIO_InitStruct);

  /* CAN1 RX GPIO pin configuration */
  GPIO_InitStruct.Pin = CANx_RX_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Alternate =  CANx_RX_AF;

  HAL_GPIO_Init(CANx_RX_GPIO_PORT, &GPIO_InitStruct);

  /* Configure the CAN peripheral #######################################*/
  CAN_HandleTypeDef CanHandle;
  CanHandle.Instance = CANx;

  CanHandle.Init.TTCM = DISABLE;
  CanHandle.Init.ABOM = DISABLE;
  CanHandle.Init.AWUM = DISABLE;
  CanHandle.Init.NART = DISABLE;
  CanHandle.Init.RFLM = DISABLE;
  CanHandle.Init.TXFP = DISABLE;
  CanHandle.Init.Mode = CAN_MODE_NORMAL;
  CanHandle.Init.SJW = CAN_SJW_1TQ;
  CanHandle.Init.BS1 = CAN_BS1_14TQ;	// this will give 1Mbit/s @ 168 MHz
  CanHandle.Init.BS2 = CAN_BS2_6TQ;
  CanHandle.Init.Prescaler = 2;

  if(HAL_CAN_Init(&CanHandle) != HAL_OK)
  {
    /* Initialization Error */
    ASSERT(0);
  }

  /* Configure the CAN Filter ###########################################*/
  CAN_FilterConfTypeDef  sFilterConfig;
  sFilterConfig.FilterNumber = 14;
  sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
  sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
  sFilterConfig.FilterIdHigh = 0x0000;
  sFilterConfig.FilterIdLow = 0x0000;
  sFilterConfig.FilterMaskIdHigh = 0x0000;
  sFilterConfig.FilterMaskIdLow = 0x0000;
  sFilterConfig.FilterFIFOAssignment = 0;
  sFilterConfig.FilterActivation = ENABLE;
  sFilterConfig.BankNumber = 14;

  if(HAL_CAN_ConfigFilter(&CanHandle, &sFilterConfig) != HAL_OK)
    ASSERT(0);

  RX_queue = xQueueCreate(10, sizeof(CANpacket));
  ASSERT(RX_queue);
  TX_queue = xQueueCreate(10, sizeof(CANpacket));
  ASSERT(TX_queue);

  TaskParameters_t p = task_parameter;
  p.uxPriority |= priority;
  MemoryRegion_t region={ this, 32, portMPU_REGION_READ_WRITE };
  p.xRegions[1]=region;
  p.pvTaskCode = (TaskFunction_t)&(can_driver_t::run);
  task_t task (p); // task object will be destroyed but task will stay alive


  uint32_t prioritygroup = NVIC_GetPriorityGrouping();

  NVIC_SetPriority(CAN2_RX0_IRQn, NVIC_EncodePriority(prioritygroup, 15, 0));
  NVIC_EnableIRQ(CAN2_RX0_IRQn);
  NVIC_SetPriority(CAN2_TX_IRQn, NVIC_EncodePriority(prioritygroup, 15, 0));
  NVIC_EnableIRQ(CAN2_TX_IRQn);

  CAN2->IER |= CAN_IT_FMP0; // enable CAN2 FIFO 0 RX interrupt
  }
