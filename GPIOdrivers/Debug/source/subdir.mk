################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/GPIO.c \
../source/main.c 

OBJS += \
./source/GPIO.o \
./source/main.o 

C_DEPS += \
./source/GPIO.d \
./source/main.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCR_INTEGER_PRINTF -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DCPU_MKL25Z128VFM4 -DCPU_MKL25Z128VFM4_cm0plus -D__REDLIB__ -I"/home/yvanox/Documents/workspace/ARM/KL25/KL25Z-DeviceDrivers/GPIOdrivers/source" -I"/home/yvanox/Documents/workspace/ARM/KL25/KL25Z-DeviceDrivers/GPIOdrivers" -I"/home/yvanox/Documents/workspace/ARM/KL25/KL25Z-DeviceDrivers/GPIOdrivers/CMSIS" -I"/home/yvanox/Documents/workspace/ARM/KL25/KL25Z-DeviceDrivers/GPIOdrivers/startup" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


