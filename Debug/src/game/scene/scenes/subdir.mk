################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/game/scene/scenes/credit_scene.c \
../src/game/scene/scenes/game_scene.c \
../src/game/scene/scenes/new_game_scene.c \
../src/game/scene/scenes/title_screen_scene.c 

C_DEPS += \
./src/game/scene/scenes/credit_scene.d \
./src/game/scene/scenes/game_scene.d \
./src/game/scene/scenes/new_game_scene.d \
./src/game/scene/scenes/title_screen_scene.d 

OBJS += \
./src/game/scene/scenes/credit_scene.o \
./src/game/scene/scenes/game_scene.o \
./src/game/scene/scenes/new_game_scene.o \
./src/game/scene/scenes/title_screen_scene.o 


# Each subdirectory must supply rules for building sources it contributes
src/game/scene/scenes/%.o: ../src/game/scene/scenes/%.c src/game/scene/scenes/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__LPC17XX__ -D__REDLIB__ -O0 -fno-common -g3 -gdwarf-4 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m3 -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-game-2f-scene-2f-scenes

clean-src-2f-game-2f-scene-2f-scenes:
	-$(RM) ./src/game/scene/scenes/credit_scene.d ./src/game/scene/scenes/credit_scene.o ./src/game/scene/scenes/game_scene.d ./src/game/scene/scenes/game_scene.o ./src/game/scene/scenes/new_game_scene.d ./src/game/scene/scenes/new_game_scene.o ./src/game/scene/scenes/title_screen_scene.d ./src/game/scene/scenes/title_screen_scene.o

.PHONY: clean-src-2f-game-2f-scene-2f-scenes

