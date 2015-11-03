################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FreeRTOS/MemoryManager/heap_tlsf.c \
../FreeRTOS/MemoryManager/tlsf.c 

OBJS += \
./FreeRTOS/MemoryManager/heap_tlsf.o \
./FreeRTOS/MemoryManager/tlsf.o 

C_DEPS += \
./FreeRTOS/MemoryManager/heap_tlsf.d \
./FreeRTOS/MemoryManager/tlsf.d 


# Each subdirectory must supply rules for building sources it contributes
FreeRTOS/MemoryManager/%.o: ../FreeRTOS/MemoryManager/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DUSE_FULL_ASSERT -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DSTM32F407xx -DUSE_HAL_DRIVER -DHSE_VALUE=8000000 -I"/home/mnl/Dokumente/RZS/workspace/rzs2_stm32f4/system/STM324xG_EVAL" -I"/home/mnl/Dokumente/RZS/workspace/rzs2_stm32f4/FreeRTOS/MemoryManager" -I"/home/mnl/Dokumente/RZS/workspace/rzs2_stm32f4/include" -I"/home/mnl/Dokumente/RZS/workspace/rzs2_stm32f4/system/include" -I"/home/mnl/Dokumente/RZS/workspace/rzs2_stm32f4/system/include/cmsis" -I"/home/mnl/Dokumente/RZS/workspace/rzs2_stm32f4/system/include/stm32f4-hal" -I"/home/mnl/Dokumente/RZS/workspace/rzs2_stm32f4/FreeRTOS/include" -I"/home/mnl/Dokumente/RZS/workspace/rzs2_stm32f4/FreeRTOS/ARM_CM3_MPU" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


