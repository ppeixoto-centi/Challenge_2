################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Project/Sensors/SHT31.c 

OBJS += \
./Core/Project/Sensors/SHT31.o 

C_DEPS += \
./Core/Project/Sensors/SHT31.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Project/Sensors/%.o Core/Project/Sensors/%.su Core/Project/Sensors/%.cyclo: ../Core/Project/Sensors/%.c Core/Project/Sensors/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xC -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/ppeixoto/OneDrive - CENTI/Ambiente de Trabalho/Challenge_2/Core/Project/Manager" -I"C:/Users/ppeixoto/OneDrive - CENTI/Ambiente de Trabalho/Challenge_2/Core/Project/UI" -I"C:/Users/ppeixoto/OneDrive - CENTI/Ambiente de Trabalho/Challenge_2/Core/Project/Sensors" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Project-2f-Sensors

clean-Core-2f-Project-2f-Sensors:
	-$(RM) ./Core/Project/Sensors/SHT31.cyclo ./Core/Project/Sensors/SHT31.d ./Core/Project/Sensors/SHT31.o ./Core/Project/Sensors/SHT31.su

.PHONY: clean-Core-2f-Project-2f-Sensors

