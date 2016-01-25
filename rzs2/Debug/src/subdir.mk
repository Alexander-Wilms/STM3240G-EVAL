################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/button.cpp \
../src/lcd.cpp \
../src/main.cpp \
../src/system_support.cpp \
../src/systick.cpp 

OBJS += \
./src/button.o \
./src/lcd.o \
./src/main.o \
./src/system_support.o \
./src/systick.o 

CPP_DEPS += \
./src/button.d \
./src/lcd.d \
./src/main.d \
./src/system_support.d \
./src/systick.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C++ Compiler'
	arm-none-eabi-g++ -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DUSE_FULL_ASSERT -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DSTM32F407xx -DUSE_HAL_DRIVER -DHSE_VALUE=8000000 -I"C:\Labor_2_RZS\rzs2_stm32f4\system\STM324xG_EVAL" -I"C:\Labor_2_RZS\rzs2_stm32f4\FreeRTOS\MemoryManager" -I"C:\Labor_2_RZS\rzs2_stm32f4\include" -I"C:\Labor_2_RZS\rzs2_stm32f4\system\include" -I"C:\Labor_2_RZS\rzs2_stm32f4\system\include\cmsis" -I"C:\Labor_2_RZS\rzs2_stm32f4\system\include\stm32f4-hal" -I"C:\Labor_2_RZS\rzs2_stm32f4\FreeRTOS\include" -I"C:\Labor_2_RZS\rzs2_stm32f4\FreeRTOS\ARM_CM3_MPU" -I"C:\Labor_2_RZS\rzs2_stm32f4\FreeRTOS\ARM_CM3_MPU" -I"C:\Labor_2_RZS\rzs2_stm32f4\FreeRTOS\include" -I"C:\Labor_2_RZS\rzs2_stm32f4\system\STM324xG_EVAL" -std=gnu++11 -fabi-version=0 -fno-exceptions -fno-rtti -fno-use-cxa-atexit -fno-threadsafe-statics -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


