################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Src/subdir.mk
-include Middleware/uart/src/subdir.mk
-include Middleware/rcc/src/subdir.mk
-include Middleware/queue/src/subdir.mk
-include Middleware/misc/src/subdir.mk
-include Middleware/handle_data_frame/src/subdir.mk
-include Middleware/gpio/src/subdir.mk
-include Middleware/flash/src/subdir.mk
-include Interrupt/subdir.mk
-include Drivers/uart/src/subdir.mk
-include Drivers/rcc/src/subdir.mk
-include Drivers/misc/src/subdir.mk
-include Drivers/gpio/src/subdir.mk
-include Drivers/flash/src/subdir.mk
-include App/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := fast_track_execise
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
fast_track_execise.elf \

MAP_FILES += \
fast_track_execise.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
fast_track_execise.list \


# All Target
all: main-build

# Main-build Target
main-build: fast_track_execise.elf secondary-outputs

# Tool invocations
fast_track_execise.elf fast_track_execise.map: $(OBJS) $(USER_OBJS) D:\stm32_cube\ sofware\embeded_stm32\fast_track_execise\STM32F103C6TX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "fast_track_execise.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"D:\stm32_cube sofware\embeded_stm32\fast_track_execise\STM32F103C6TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="fast_track_execise.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

fast_track_execise.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "fast_track_execise.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) default.size.stdout fast_track_execise.elf fast_track_execise.list fast_track_execise.map
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
