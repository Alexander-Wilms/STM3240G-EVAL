/*
 * candriver.h
 *
 *  Created on: Dec 11, 2015
 *      Author: schaefer
 */

#ifndef CANDRIVER_H_
#define CANDRIVER_H_

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_can.h"

namespace CAN_driver_ISR // need a namespace to declare friend functions
{
  extern "C" void CAN2_RX0_IRQHandler(void);
  extern "C" void CAN2_TX_IRQHandler(void);
}

class can_driver_t
{
  friend void CAN_driver_ISR::CAN2_RX0_IRQHandler(void);
  friend void CAN_driver_ISR::CAN2_TX_IRQHandler(void);
public:
  can_driver_t (uint8_t priority);

  typedef struct CANpacket
  {
    uint16_t id;
    uint16_t dlc;
    union
    {
      uint8_t data_b[8];
      uint32_t data_w[2];
    };
  };

  bool receive( CANpacket &packet, uint32_t wait=0xffffffff)
  {
    return xQueueReceive( RX_queue, &packet, wait);
  }
  static void run(void *);
  inline BaseType_t deliver_RX_packet( CanRxMsgTypeDef *packet)
  {
    BaseType_t task_woken=0;
    xQueueSendFromISR( RX_queue, packet, &task_woken);
    return task_woken;
  }
  bool send_can_packet( const CANpacket &msg);
  bool send( const CANpacket &packet, uint32_t wait=0xffffffff)
  {
    /* Temporarily disable Transmit mailbox empty Interrupt */
    CAN2->IER &= ~CAN_IT_TME;
    if ( send_can_packet( packet) == true) // hardware FIFO
      {
      /* Enable Transmit mailbox empty Interrupt */
      CAN2->IER |= CAN_IT_TME;
      return true;
      }

    bool ret = xQueueSend( TX_queue, &packet, wait);

    /* Enable Transmit mailbox empty Interrupt */
    CAN2->IER |= CAN_IT_TME;

    return ret;
  }
  inline void * operator new( size_t size)
  {
	  return pvPortMalloc( size);
  }
private:
  xQueueHandle RX_queue;
  xQueueHandle TX_queue;
};

#endif /* CANDRIVER_H_ */
