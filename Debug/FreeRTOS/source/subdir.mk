################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FreeRTOS/source/croutine.c \
../FreeRTOS/source/event_groups.c \
../FreeRTOS/source/list.c \
../FreeRTOS/source/queue.c \
../FreeRTOS/source/tasks.c \
../FreeRTOS/source/timers.c 

OBJS += \
./FreeRTOS/source/croutine.o \
./FreeRTOS/source/event_groups.o \
./FreeRTOS/source/list.o \
./FreeRTOS/source/queue.o \
./FreeRTOS/source/tasks.o \
./FreeRTOS/source/timers.o 

C_DEPS += \
./FreeRTOS/source/croutine.d \
./FreeRTOS/source/event_groups.d \
./FreeRTOS/source/list.d \
./FreeRTOS/source/queue.d \
./FreeRTOS/source/tasks.d \
./FreeRTOS/source/timers.d 


# Each subdirectory must supply rules for building sources it contributes
FreeRTOS/source/%.o: ../FreeRTOS/source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DUSE_FULL_ASSERT -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DSTM32F407xx -DUSE_HAL_DRIVER -DHSE_VALUE=8000000 -I"/home/mnl/Dokumente/RZS/workspace/rzs2_stm32f4/system/STM324xG_EVAL" -I"/home/mnl/Dokumente/RZS/workspace/rzs2_stm32f4/FreeRTOS/MemoryManager" -I"/home/mnl/Dokumente/RZS/workspace/rzs2_stm32f4/include" -I"/home/mnl/Dokumente/RZS/workspace/rzs2_stm32f4/system/include" -I"/home/mnl/Dokumente/RZS/workspace/rzs2_stm32f4/system/include/cmsis" -I"/home/mnl/Dokumente/RZS/workspace/rzs2_stm32f4/system/include/stm32f4-hal" -I"/home/mnl/Dokumente/RZS/workspace/rzs2_stm32f4/FreeRTOS/include" -I"/home/mnl/Dokumente/RZS/workspace/rzs2_stm32f4/FreeRTOS/ARM_CM3_MPU" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


