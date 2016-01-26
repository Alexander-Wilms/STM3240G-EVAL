################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../system/src/diag/Trace.c \
../system/src/diag/trace_impl.c 

OBJS += \
./system/src/diag/Trace.o \
./system/src/diag/trace_impl.o 

C_DEPS += \
./system/src/diag/Trace.d \
./system/src/diag/trace_impl.d 


# Each subdirectory must supply rules for building sources it contributes
system/src/diag/%.o: ../system/src/diag/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DUSE_FULL_ASSERT -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DSTM32F407xx -DUSE_HAL_DRIVER -DHSE_VALUE=8000000 -I"C:\Labor_2_RZS\rzs2_stm32f4\system\STM324xG_EVAL" -I"C:\Labor_2_RZS\rzs2_stm32f4\FreeRTOS\MemoryManager" -I"C:\Labor_2_RZS\rzs2_stm32f4\include" -I"C:\Labor_2_RZS\rzs2_stm32f4\system\include" -I"C:\Labor_2_RZS\rzs2_stm32f4\system\include\cmsis" -I"C:\Labor_2_RZS\rzs2_stm32f4\system\include\stm32f4-hal" -I"C:\Labor_2_RZS\rzs2_stm32f4\FreeRTOS\include" -I"C:\Labor_2_RZS\rzs2_stm32f4\FreeRTOS\ARM_CM3_MPU" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


