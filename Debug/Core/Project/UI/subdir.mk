################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Project/UI/UI.c 

OBJS += \
./Core/Project/UI/UI.o 

C_DEPS += \
./Core/Project/UI/UI.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Project/UI/%.o Core/Project/UI/%.su Core/Project/UI/%.cyclo: ../Core/Project/UI/%.c Core/Project/UI/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xC -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/ppeixoto/OneDrive - CENTI/Ambiente de Trabalho/Centi/STM32/Challenge_2/Challenge_2/Core/Project/Manager" -I"C:/Users/ppeixoto/OneDrive - CENTI/Ambiente de Trabalho/Centi/STM32/Challenge_2/Challenge_2/Core/Project/UI" -I"C:/Users/ppeixoto/OneDrive - CENTI/Ambiente de Trabalho/Centi/STM32/Challenge_2/Challenge_2/Core/Project/Sensors" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Project-2f-UI

clean-Core-2f-Project-2f-UI:
	-$(RM) ./Core/Project/UI/UI.cyclo ./Core/Project/UI/UI.d ./Core/Project/UI/UI.o ./Core/Project/UI/UI.su

.PHONY: clean-Core-2f-Project-2f-UI

