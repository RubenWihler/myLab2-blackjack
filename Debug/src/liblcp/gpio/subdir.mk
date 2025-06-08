################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/liblcp/gpio/gpio.c \
../src/liblcp/gpio/gpio_interrupts.c 

C_DEPS += \
./src/liblcp/gpio/gpio.d \
./src/liblcp/gpio/gpio_interrupts.d 

OBJS += \
./src/liblcp/gpio/gpio.o \
./src/liblcp/gpio/gpio_interrupts.o 


# Each subdirectory must supply rules for building sources it contributes
src/liblcp/gpio/%.o: ../src/liblcp/gpio/%.c src/liblcp/gpio/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__LPC17XX__ -D__REDLIB__ -O0 -fno-common -g3 -gdwarf-4 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m3 -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-liblcp-2f-gpio

clean-src-2f-liblcp-2f-gpio:
	-$(RM) ./src/liblcp/gpio/gpio.d ./src/liblcp/gpio/gpio.o ./src/liblcp/gpio/gpio_interrupts.d ./src/liblcp/gpio/gpio_interrupts.o

.PHONY: clean-src-2f-liblcp-2f-gpio

