################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/liblcp/rendering/sprite/sprite.c 

C_DEPS += \
./src/liblcp/rendering/sprite/sprite.d 

OBJS += \
./src/liblcp/rendering/sprite/sprite.o 


# Each subdirectory must supply rules for building sources it contributes
src/liblcp/rendering/sprite/%.o: ../src/liblcp/rendering/sprite/%.c src/liblcp/rendering/sprite/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__LPC17XX__ -D__REDLIB__ -O0 -fno-common -g3 -gdwarf-4 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m3 -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-liblcp-2f-rendering-2f-sprite

clean-src-2f-liblcp-2f-rendering-2f-sprite:
	-$(RM) ./src/liblcp/rendering/sprite/sprite.d ./src/liblcp/rendering/sprite/sprite.o

.PHONY: clean-src-2f-liblcp-2f-rendering-2f-sprite

