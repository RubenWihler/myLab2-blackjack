################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/game/scene/scene.c 

C_DEPS += \
./src/game/scene/scene.d 

OBJS += \
./src/game/scene/scene.o 


# Each subdirectory must supply rules for building sources it contributes
src/game/scene/%.o: ../src/game/scene/%.c src/game/scene/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__LPC17XX__ -D__REDLIB__ -O0 -fno-common -g3 -gdwarf-4 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m3 -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-game-2f-scene

clean-src-2f-game-2f-scene:
	-$(RM) ./src/game/scene/scene.d ./src/game/scene/scene.o

.PHONY: clean-src-2f-game-2f-scene

