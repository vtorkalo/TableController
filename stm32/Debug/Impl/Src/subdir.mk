################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Impl/Src/app.c \
../Impl/Src/appState.c \
../Impl/Src/bridge.c \
../Impl/Src/buttons.c \
../Impl/Src/ee24.c \
../Impl/Src/encoder.c \
../Impl/Src/power.c \
../Impl/Src/powerMonitor.c 

OBJS += \
./Impl/Src/app.o \
./Impl/Src/appState.o \
./Impl/Src/bridge.o \
./Impl/Src/buttons.o \
./Impl/Src/ee24.o \
./Impl/Src/encoder.o \
./Impl/Src/power.o \
./Impl/Src/powerMonitor.o 

C_DEPS += \
./Impl/Src/app.d \
./Impl/Src/appState.d \
./Impl/Src/bridge.d \
./Impl/Src/buttons.d \
./Impl/Src/ee24.d \
./Impl/Src/encoder.d \
./Impl/Src/power.d \
./Impl/Src/powerMonitor.d 


# Each subdirectory must supply rules for building sources it contributes
Impl/Src/app.o: ../Impl/Src/app.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32F103xE -DUSE_HAL_DRIVER -DDEBUG -c -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Impl/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Impl/Src/app.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Impl/Src/appState.o: ../Impl/Src/appState.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32F103xE -DUSE_HAL_DRIVER -DDEBUG -c -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Impl/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Impl/Src/appState.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Impl/Src/bridge.o: ../Impl/Src/bridge.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32F103xE -DUSE_HAL_DRIVER -DDEBUG -c -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Impl/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Impl/Src/bridge.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Impl/Src/buttons.o: ../Impl/Src/buttons.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32F103xE -DUSE_HAL_DRIVER -DDEBUG -c -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Impl/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Impl/Src/buttons.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Impl/Src/ee24.o: ../Impl/Src/ee24.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32F103xE -DUSE_HAL_DRIVER -DDEBUG -c -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Impl/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Impl/Src/ee24.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Impl/Src/encoder.o: ../Impl/Src/encoder.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32F103xE -DUSE_HAL_DRIVER -DDEBUG -c -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Impl/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Impl/Src/encoder.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Impl/Src/power.o: ../Impl/Src/power.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32F103xE -DUSE_HAL_DRIVER -DDEBUG -c -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Impl/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Impl/Src/power.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Impl/Src/powerMonitor.o: ../Impl/Src/powerMonitor.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32F103xE -DUSE_HAL_DRIVER -DDEBUG -c -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Impl/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Impl/Src/powerMonitor.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

