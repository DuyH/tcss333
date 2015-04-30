################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../structV1.c \
../structV2.c \
../structV3.c \
../structV4FAIL.c \
../structV5.c 

OBJS += \
./structV1.o \
./structV2.o \
./structV3.o \
./structV4FAIL.o \
./structV5.o 

C_DEPS += \
./structV1.d \
./structV2.d \
./structV3.d \
./structV4FAIL.d \
./structV5.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


