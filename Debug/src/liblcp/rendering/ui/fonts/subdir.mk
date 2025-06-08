################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/liblcp/rendering/ui/fonts/fonts.c 

C_DEPS += \
./src/liblcp/rendering/ui/fonts/fonts.d 

OBJS += \
./src/liblcp/rendering/ui/fonts/fonts.o 


# Each subdirectory must supply rules for building sources it contributes
src/liblcp/rendering/ui/fonts/%.o: ../src/liblcp/rendering/ui/fonts/%.c src/liblcp/rendering/ui/fonts/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__LPC17XX__ -D__REDLIB__ -O0 -fno-common -g3 -gdwarf-4 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m3 -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-liblcp-2f-rendering-2f-ui-2f-fonts

clean-src-2f-liblcp-2f-rendering-2f-ui-2f-fonts:
	-$(RM) ./src/liblcp/rendering/ui/fonts/fonts.d ./src/liblcp/rendering/ui/fonts/fonts.o

.PHONY: clean-src-2f-liblcp-2f-rendering-2f-ui-2f-fonts

