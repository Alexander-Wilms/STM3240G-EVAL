/*
 * system_support.cpp
 *
 *  Created on: Nov 2, 2015
 *      Author: schaefer
 */

#include "stm32f4xx_hal.h"
#include "FreeRTOSConfig.h"

extern "C" void vPortInitMemory ();

void init_system(void)
{
	SCB->SHCSR |= (SCB_SHCSR_BUSFAULTENA_Msk | SCB_SHCSR_MEMFAULTENA_Msk
			| SCB_SHCSR_USGFAULTENA_Msk);

	extern int _s_system_ram;
	extern int _e_system_ram;
	int *ptr;
	for (ptr = &_s_system_ram; ptr < &_e_system_ram; ++ptr)
		*ptr = 0;

	vPortInitMemory();

}

void init_FreeRTOS_reporting (void)
{
	// initialize PORT I as output for CPU watch
	GPIO_InitTypeDef GPIO_InitStructure;

	__HAL_RCC_GPIOI_CLK_ENABLE();

	/* Configure Port 'I' 4567 for poor man's DAC */
	GPIO_InitStructure.Pin = 0xf0;
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	GPIO_InitStructure.Speed = GPIO_SPEED_FAST;
	HAL_GPIO_Init(GPIOI, &GPIO_InitStructure);

	__HAL_RCC_GPIOE_CLK_ENABLE();

	/* Configure PE 0 */
	GPIO_InitStructure.Pin = 0x01;
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	GPIO_InitStructure.Speed = GPIO_SPEED_FAST;

	HAL_GPIO_Init(GPIOE, &GPIO_InitStructure);
}

extern "C" void vApplicationIdleHook(void)
{
}

extern "C" void vApplicationReturnFromTaskProcedureHook(void)
{
	asm("bkpt 0");
}
