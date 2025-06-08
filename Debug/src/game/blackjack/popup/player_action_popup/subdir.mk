################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/game/blackjack/popup/player_action_popup/player_action_popup.c 

C_DEPS += \
./src/game/blackjack/popup/player_action_popup/player_action_popup.d 

OBJS += \
./src/game/blackjack/popup/player_action_popup/player_action_popup.o 


# Each subdirectory must supply rules for building sources it contributes
src/game/blackjack/popup/player_action_popup/%.o: ../src/game/blackjack/popup/player_action_popup/%.c src/game/blackjack/popup/player_action_popup/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__LPC17XX__ -D__REDLIB__ -O0 -fno-common -g3 -gdwarf-4 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m3 -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-game-2f-blackjack-2f-popup-2f-player_action_popup

clean-src-2f-game-2f-blackjack-2f-popup-2f-player_action_popup:
	-$(RM) ./src/game/blackjack/popup/player_action_popup/player_action_popup.d ./src/game/blackjack/popup/player_action_popup/player_action_popup.o

.PHONY: clean-src-2f-game-2f-blackjack-2f-popup-2f-player_action_popup

