################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/flash/src/flash_driver.c 

OBJS += \
./Drivers/flash/src/flash_driver.o 

C_DEPS += \
./Drivers/flash/src/flash_driver.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/flash/src/%.o Drivers/flash/src/%.su: ../Drivers/flash/src/%.c Drivers/flash/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER -c -I../Inc -I"D:/stm32_cube sofware/embeded_stm32/fast_track_execise/App" -I"D:/stm32_cube sofware/embeded_stm32/fast_track_execise/Drivers/inc" -I"D:/stm32_cube sofware/embeded_stm32/fast_track_execise/Interrupt" -I"D:/stm32_cube sofware/embeded_stm32/fast_track_execise/Drivers/flash/include" -I"D:/stm32_cube sofware/embeded_stm32/fast_track_execise/Drivers/gpio/include" -I"D:/stm32_cube sofware/embeded_stm32/fast_track_execise/Drivers/misc/include" -I"D:/stm32_cube sofware/embeded_stm32/fast_track_execise/Drivers/rcc/include" -I"D:/stm32_cube sofware/embeded_stm32/fast_track_execise/Drivers/uart/include" -I"D:/stm32_cube sofware/embeded_stm32/fast_track_execise/Middleware/flash/include" -I"D:/stm32_cube sofware/embeded_stm32/fast_track_execise/Middleware/gpio/include" -I"D:/stm32_cube sofware/embeded_stm32/fast_track_execise/Middleware/handle_data_frame/include" -I"D:/stm32_cube sofware/embeded_stm32/fast_track_execise/Middleware/misc/include" -I"D:/stm32_cube sofware/embeded_stm32/fast_track_execise/Middleware/queue/include" -I"D:/stm32_cube sofware/embeded_stm32/fast_track_execise/Middleware/rcc/include" -I"D:/stm32_cube sofware/embeded_stm32/fast_track_execise/Middleware/uart/include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-flash-2f-src

clean-Drivers-2f-flash-2f-src:
	-$(RM) ./Drivers/flash/src/flash_driver.d ./Drivers/flash/src/flash_driver.o ./Drivers/flash/src/flash_driver.su

.PHONY: clean-Drivers-2f-flash-2f-src

