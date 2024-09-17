################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../component/lists/fsl_component_generic_list.c 

C_DEPS += \
./component/lists/fsl_component_generic_list.d 

OBJS += \
./component/lists/fsl_component_generic_list.o 


# Each subdirectory must supply rules for building sources it contributes
component/lists/%.o: ../component/lists/%.c component/lists/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_KW45B41Z83AFTA -DCPU_KW45B41Z83AFTA_cm33 -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DSERIAL_PORT_TYPE_UART=1 -DSDK_OS_FREE_RTOS -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\bakra\Desktop\KW45B41Z\freertos_demo\board" -I"C:\Users\bakra\Desktop\KW45B41Z\freertos_demo\source" -I"C:\Users\bakra\Desktop\KW45B41Z\freertos_demo\drivers" -I"C:\Users\bakra\Desktop\KW45B41Z\freertos_demo\component\lists" -I"C:\Users\bakra\Desktop\KW45B41Z\freertos_demo\CMSIS" -I"C:\Users\bakra\Desktop\KW45B41Z\freertos_demo\component\serial_manager" -I"C:\Users\bakra\Desktop\KW45B41Z\freertos_demo\device" -I"C:\Users\bakra\Desktop\KW45B41Z\freertos_demo\component\uart" -I"C:\Users\bakra\Desktop\KW45B41Z\freertos_demo\utilities" -I"C:\Users\bakra\Desktop\KW45B41Z\freertos_demo\freertos\freertos_kernel\include" -I"C:\Users\bakra\Desktop\KW45B41Z\freertos_demo\freertos\freertos_kernel\portable\GCC\ARM_CM33_NTZ\non_secure" -O0 -fno-common -g3 -gdwarf-4 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m33 -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-component-2f-lists

clean-component-2f-lists:
	-$(RM) ./component/lists/fsl_component_generic_list.d ./component/lists/fsl_component_generic_list.o

.PHONY: clean-component-2f-lists

