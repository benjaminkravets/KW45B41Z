################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../startup/startup_kw45b41z83.c 

C_DEPS += \
./startup/startup_kw45b41z83.d 

OBJS += \
./startup/startup_kw45b41z83.o 


# Each subdirectory must supply rules for building sources it contributes
startup/%.o: ../startup/%.c startup/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_KW45B41Z83AFTA -DCPU_KW45B41Z83AFTA_cm33 -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DSERIAL_PORT_TYPE_UART=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\bakra\Desktop\KW45B41Z\spirate\board" -I"C:\Users\bakra\Desktop\KW45B41Z\spirate\drivers" -I"C:\Users\bakra\Desktop\KW45B41Z\spirate\component\lists" -I"C:\Users\bakra\Desktop\KW45B41Z\spirate\CMSIS" -I"C:\Users\bakra\Desktop\KW45B41Z\spirate\component\serial_manager" -I"C:\Users\bakra\Desktop\KW45B41Z\spirate\device" -I"C:\Users\bakra\Desktop\KW45B41Z\spirate\utilities" -I"C:\Users\bakra\Desktop\KW45B41Z\spirate\component\uart" -I"C:\Users\bakra\Desktop\KW45B41Z\spirate\source" -O0 -fno-common -g3 -gdwarf-4 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m33 -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-startup

clean-startup:
	-$(RM) ./startup/startup_kw45b41z83.d ./startup/startup_kw45b41z83.o

.PHONY: clean-startup

