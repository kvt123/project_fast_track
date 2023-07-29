################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middleware/handle_data_frame/src/handle_data_frame.c 

OBJS += \
./Middleware/handle_data_frame/src/handle_data_frame.o 

C_DEPS += \
./Middleware/handle_data_frame/src/handle_data_frame.d 


# Each subdirectory must supply rules for building sources it contributes
Middleware/handle_data_frame/src/%.o Middleware/handle_data_frame/src/%.su: ../Middleware/handle_data_frame/src/%.c Middleware/handle_data_frame/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER -c -I../Inc -I"D:/stm32_cube sofware/embeded_stm32/fast_track_execise/App" -I"D:/stm32_cube sofware/embeded_stm32/fast_track_execise/Drivers/inc" -I"D:/stm32_cube sofware/embeded_stm32/fast_track_execise/Interrupt" -I"D:/stm32_cube sofware/embeded_stm32/fast_track_execise/Drivers/flash/include" -I"D:/stm32_cube sofware/embeded_stm32/fast_track_execise/Drivers/gpio/include" -I"D:/stm32_cube sofware/embeded_stm32/fast_track_execise/Drivers/misc/include" -I"D:/stm32_cube sofware/embeded_stm32/fast_track_execise/Drivers/rcc/include" -I"D:/stm32_cube sofware/embeded_stm32/fast_track_execise/Drivers/uart/include" -I"D:/stm32_cube sofware/embeded_stm32/fast_track_execise/Middleware/flash/include" -I"D:/stm32_cube sofware/embeded_stm32/fast_track_execise/Middleware/gpio/include" -I"D:/stm32_cube sofware/embeded_stm32/fast_track_execise/Middleware/handle_data_frame/include" -I"D:/stm32_cube sofware/embeded_stm32/fast_track_execise/Middleware/misc/include" -I"D:/stm32_cube sofware/embeded_stm32/fast_track_execise/Middleware/queue/include" -I"D:/stm32_cube sofware/embeded_stm32/fast_track_execise/Middleware/rcc/include" -I"D:/stm32_cube sofware/embeded_stm32/fast_track_execise/Middleware/uart/include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Middleware-2f-handle_data_frame-2f-src

clean-Middleware-2f-handle_data_frame-2f-src:
	-$(RM) ./Middleware/handle_data_frame/src/handle_data_frame.d ./Middleware/handle_data_frame/src/handle_data_frame.o ./Middleware/handle_data_frame/src/handle_data_frame.su

.PHONY: clean-Middleware-2f-handle_data_frame-2f-src

