################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/liblcp/rendering/utils/color_utils.c \
../src/liblcp/rendering/utils/lerp.c \
../src/liblcp/rendering/utils/rect.c 

C_DEPS += \
./src/liblcp/rendering/utils/color_utils.d \
./src/liblcp/rendering/utils/lerp.d \
./src/liblcp/rendering/utils/rect.d 

OBJS += \
./src/liblcp/rendering/utils/color_utils.o \
./src/liblcp/rendering/utils/lerp.o \
./src/liblcp/rendering/utils/rect.o 


# Each subdirectory must supply rules for building sources it contributes
src/liblcp/rendering/utils/%.o: ../src/liblcp/rendering/utils/%.c src/liblcp/rendering/utils/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__LPC17XX__ -D__REDLIB__ -O0 -fno-common -g3 -gdwarf-4 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m3 -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-liblcp-2f-rendering-2f-utils

clean-src-2f-liblcp-2f-rendering-2f-utils:
	-$(RM) ./src/liblcp/rendering/utils/color_utils.d ./src/liblcp/rendering/utils/color_utils.o ./src/liblcp/rendering/utils/lerp.d ./src/liblcp/rendering/utils/lerp.o ./src/liblcp/rendering/utils/rect.d ./src/liblcp/rendering/utils/rect.o

.PHONY: clean-src-2f-liblcp-2f-rendering-2f-utils

