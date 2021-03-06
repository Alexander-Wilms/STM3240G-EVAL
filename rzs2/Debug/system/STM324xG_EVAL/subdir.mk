################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../system/STM324xG_EVAL/cs43l22.c \
../system/STM324xG_EVAL/font12.c \
../system/STM324xG_EVAL/font16.c \
../system/STM324xG_EVAL/font20.c \
../system/STM324xG_EVAL/font24.c \
../system/STM324xG_EVAL/font8.c \
../system/STM324xG_EVAL/ili9325.c \
../system/STM324xG_EVAL/stm324xg_eval.c \
../system/STM324xG_EVAL/stm324xg_eval_audio.c \
../system/STM324xG_EVAL/stm324xg_eval_eeprom.c \
../system/STM324xG_EVAL/stm324xg_eval_io.c \
../system/STM324xG_EVAL/stm324xg_eval_lcd.c \
../system/STM324xG_EVAL/stm324xg_eval_sd.c \
../system/STM324xG_EVAL/stm324xg_eval_sram.c \
../system/STM324xG_EVAL/stm324xg_eval_ts.c \
../system/STM324xG_EVAL/stmpe811.c 

OBJS += \
./system/STM324xG_EVAL/cs43l22.o \
./system/STM324xG_EVAL/font12.o \
./system/STM324xG_EVAL/font16.o \
./system/STM324xG_EVAL/font20.o \
./system/STM324xG_EVAL/font24.o \
./system/STM324xG_EVAL/font8.o \
./system/STM324xG_EVAL/ili9325.o \
./system/STM324xG_EVAL/stm324xg_eval.o \
./system/STM324xG_EVAL/stm324xg_eval_audio.o \
./system/STM324xG_EVAL/stm324xg_eval_eeprom.o \
./system/STM324xG_EVAL/stm324xg_eval_io.o \
./system/STM324xG_EVAL/stm324xg_eval_lcd.o \
./system/STM324xG_EVAL/stm324xg_eval_sd.o \
./system/STM324xG_EVAL/stm324xg_eval_sram.o \
./system/STM324xG_EVAL/stm324xg_eval_ts.o \
./system/STM324xG_EVAL/stmpe811.o 

C_DEPS += \
./system/STM324xG_EVAL/cs43l22.d \
./system/STM324xG_EVAL/font12.d \
./system/STM324xG_EVAL/font16.d \
./system/STM324xG_EVAL/font20.d \
./system/STM324xG_EVAL/font24.d \
./system/STM324xG_EVAL/font8.d \
./system/STM324xG_EVAL/ili9325.d \
./system/STM324xG_EVAL/stm324xg_eval.d \
./system/STM324xG_EVAL/stm324xg_eval_audio.d \
./system/STM324xG_EVAL/stm324xg_eval_eeprom.d \
./system/STM324xG_EVAL/stm324xg_eval_io.d \
./system/STM324xG_EVAL/stm324xg_eval_lcd.d \
./system/STM324xG_EVAL/stm324xg_eval_sd.d \
./system/STM324xG_EVAL/stm324xg_eval_sram.d \
./system/STM324xG_EVAL/stm324xg_eval_ts.d \
./system/STM324xG_EVAL/stmpe811.d 


# Each subdirectory must supply rules for building sources it contributes
system/STM324xG_EVAL/%.o: ../system/STM324xG_EVAL/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DUSE_FULL_ASSERT -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DSTM32F407xx -DUSE_HAL_DRIVER -DHSE_VALUE=8000000 -I"C:\Labor_2_RZS\rzs2_stm32f4\system\STM324xG_EVAL" -I"C:\Labor_2_RZS\rzs2_stm32f4\FreeRTOS\MemoryManager" -I"C:\Labor_2_RZS\rzs2_stm32f4\include" -I"C:\Labor_2_RZS\rzs2_stm32f4\system\include" -I"C:\Labor_2_RZS\rzs2_stm32f4\system\include\cmsis" -I"C:\Labor_2_RZS\rzs2_stm32f4\system\include\stm32f4-hal" -I"C:\Labor_2_RZS\rzs2_stm32f4\FreeRTOS\include" -I"C:\Labor_2_RZS\rzs2_stm32f4\FreeRTOS\ARM_CM3_MPU" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


