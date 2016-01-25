/**
@file adc.h
@brief ADC driver for STM3240G-Eval
@author: Dr. Klaus Schaefer
*/

#ifndef ADC_H_
#define ADC_H_

#include "stdint.h"
#include "common.h"

extern COMMON class adc * the_adc;

namespace C { extern "C" void ADC_IRQHandler (void); }

class adc
{
public:
  adc (void);
  inline uint16_t get_value( void) const
  {
    return value;
  }
private:
  static volatile uint16_t value;
  friend void C::ADC_IRQHandler(void);
};

#endif /* ADC_H_ */
