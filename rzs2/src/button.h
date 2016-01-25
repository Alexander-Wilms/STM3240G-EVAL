/**
  ******************************************************************************
  * @file    button.h
  * @author  Dr. Klaus Schaefer
  * @brief   header for module button
  ******************************************************************************
*/

void pushbutton_init( void); //!< init pushbutton interrupt mechanism
extern unsigned exti_count; //!< number of invocations of the EXTI INT
