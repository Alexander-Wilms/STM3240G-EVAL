/**
  ******************************************************************************
  * @file    systick.h
  * @author  Dr. Klaus Schaefer
  * @brief   header for module button
  ******************************************************************************
*/

void SysTick_init( void);
void busy_delay( unsigned time);
extern volatile unsigned tickCount;
extern volatile int mytimer;
