################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/fsl_ccm32k.c \
../drivers/fsl_clock.c \
../drivers/fsl_common.c \
../drivers/fsl_common_arm.c \
../drivers/fsl_gpio.c \
../drivers/fsl_lpuart.c \
../drivers/fsl_spc.c 

C_DEPS += \
./drivers/fsl_ccm32k.d \
./drivers/fsl_clock.d \
./drivers/fsl_common.d \
./drivers/fsl_common_arm.d \
./drivers/fsl_gpio.d \
./drivers/fsl_lpuart.d \
./drivers/fsl_spc.d 

OBJS += \
./drivers/fsl_ccm32k.o \
./drivers/fsl_clock.o \
./drivers/fsl_common.o \
./drivers/fsl_common_arm.o \
./drivers/fsl_gpio.o \
./drivers/fsl_lpuart.o \
./drivers/fsl_spc.o 


# Each subdirectory must supply rules for building sources it contributes
drivers/%.o: ../drivers/%.c drivers/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_KW45B41Z83AFTA -DCPU_KW45B41Z83AFTA_cm33 -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DSERIAL_PORT_TYPE_UART=1 -DSDK_OS_FREE_RTOS -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\bakra\Desktop\KW45B41Z\freertos_demo\board" -I"C:\Users\bakra\Desktop\KW45B41Z\freertos_demo\source" -I"C:\Users\bakra\Desktop\KW45B41Z\freertos_demo\drivers" -I"C:\Users\bakra\Desktop\KW45B41Z\freertos_demo\component\lists" -I"C:\Users\bakra\Desktop\KW45B41Z\freertos_demo\CMSIS" -I"C:\Users\bakra\Desktop\KW45B41Z\freertos_demo\component\serial_manager" -I"C:\Users\bakra\Desktop\KW45B41Z\freertos_demo\device" -I"C:\Users\bakra\Desktop\KW45B41Z\freertos_demo\component\uart" -I"C:\Users\bakra\Desktop\KW45B41Z\freertos_demo\utilities" -I"C:\Users\bakra\Desktop\KW45B41Z\freertos_demo\freertos\freertos_kernel\include" -I"C:\Users\bakra\Desktop\KW45B41Z\freertos_demo\freertos\freertos_kernel\portable\GCC\ARM_CM33_NTZ\non_secure" -O0 -fno-common -g3 -gdwarf-4 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m33 -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-drivers

clean-drivers:
	-$(RM) ./drivers/fsl_ccm32k.d ./drivers/fsl_ccm32k.o ./drivers/fsl_clock.d ./drivers/fsl_clock.o ./drivers/fsl_common.d ./drivers/fsl_common.o ./drivers/fsl_common_arm.d ./drivers/fsl_common_arm.o ./drivers/fsl_gpio.d ./drivers/fsl_gpio.o ./drivers/fsl_lpuart.d ./drivers/fsl_lpuart.o ./drivers/fsl_spc.d ./drivers/fsl_spc.o

.PHONY: clean-drivers

