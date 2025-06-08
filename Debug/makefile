################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/liblcp/utils/string_utils/subdir.mk
-include src/liblcp/utils/dyn_array/subdir.mk
-include src/liblcp/utils/subdir.mk
-include src/liblcp/time/subdir.mk
-include src/liblcp/spi/subdir.mk
-include src/liblcp/rendering/utils/subdir.mk
-include src/liblcp/rendering/ui/fonts/subdir.mk
-include src/liblcp/rendering/ui/elements/trigger_zone/subdir.mk
-include src/liblcp/rendering/ui/elements/textbox/subdir.mk
-include src/liblcp/rendering/sprite/subdir.mk
-include src/liblcp/rendering/screen/subdir.mk
-include src/liblcp/rendering/drawing/subdir.mk
-include src/liblcp/log/subdir.mk
-include src/liblcp/ledrgb/subdir.mk
-include src/liblcp/inputs/touch_screen/subdir.mk
-include src/liblcp/inputs/subdir.mk
-include src/liblcp/gpio/subdir.mk
-include src/game/scene/scenes/subdir.mk
-include src/game/scene/subdir.mk
-include src/game/blackjack/render/subdir.mk
-include src/game/blackjack/popup/player_action_popup/subdir.mk
-include src/game/blackjack/popup/bet_popup/subdir.mk
-include src/game/blackjack/card/subdir.mk
-include src/game/blackjack/subdir.mk
-include src/game/subdir.mk
-include src/subdir.mk
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := myLab2_blackjack
BUILD_ARTIFACT_EXTENSION := axf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all:
	+@$(MAKE) --no-print-directory main-build && $(MAKE) --no-print-directory post-build

# Main-build Target
main-build: myLab2_blackjack.axf

# Tool invocations
myLab2_blackjack.axf: $(OBJS) $(USER_OBJS) makefile $(OPTIONAL_TOOL_DEPS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"/home/wihler/labs/micro/project_workspace/myLab2_blackjack/Debug" -L"/home/wihler/labs/micro/project_workspace/myLab2_blackjack/src/libs" -Xlinker -Map="myLab2_blackjack.map" -Xlinker --cref -Xlinker --gc-sections -Xlinker -print-memory-usage -mcpu=cortex-m3 -mthumb -T myLab2_blackjack_Debug.ld -o "myLab2_blackjack.axf" $(OBJS) $(USER_OBJS) $(LIBS) -lMyLab_lib
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) myLab2_blackjack.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "myLab2_blackjack.axf"; # arm-none-eabi-objcopy -v -O binary "myLab2_blackjack.axf" "myLab2_blackjack.bin" ; # checksum -p LPC1769 -d "myLab2_blackjack.bin";
	-@echo ' '

.PHONY: all clean dependents main-build post-build

-include ../makefile.targets
