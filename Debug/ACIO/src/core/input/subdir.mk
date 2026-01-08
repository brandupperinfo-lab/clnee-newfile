################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ACIO/src/core/input/EdgeInputController.c \
../ACIO/src/core/input/NthInputController.c 

OBJS += \
./ACIO/src/core/input/EdgeInputController.o \
./ACIO/src/core/input/NthInputController.o 

C_DEPS += \
./ACIO/src/core/input/EdgeInputController.d \
./ACIO/src/core/input/NthInputController.d 


# Each subdirectory must supply rules for building sources it contributes
ACIO/src/core/input/%.o ACIO/src/core/input/%.su ACIO/src/core/input/%.cyclo: ../ACIO/src/core/input/%.c ACIO/src/core/input/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G030xx -c -I../Core/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/vkdls/Documents/STM32CubeIDE/workspace_1.9.0/Ecoit-USCUV-G030F6/ACIO/src" -Og -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-ACIO-2f-src-2f-core-2f-input

clean-ACIO-2f-src-2f-core-2f-input:
	-$(RM) ./ACIO/src/core/input/EdgeInputController.cyclo ./ACIO/src/core/input/EdgeInputController.d ./ACIO/src/core/input/EdgeInputController.o ./ACIO/src/core/input/EdgeInputController.su ./ACIO/src/core/input/NthInputController.cyclo ./ACIO/src/core/input/NthInputController.d ./ACIO/src/core/input/NthInputController.o ./ACIO/src/core/input/NthInputController.su

.PHONY: clean-ACIO-2f-src-2f-core-2f-input

