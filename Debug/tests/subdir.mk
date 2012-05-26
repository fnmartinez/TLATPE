################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../tests/AutomataTest.c \
../tests/GrammarTest.c \
../tests/UtilTest.c 

OBJS += \
./tests/AutomataTest.o \
./tests/GrammarTest.o \
./tests/UtilTest.o 

C_DEPS += \
./tests/AutomataTest.d \
./tests/GrammarTest.d \
./tests/UtilTest.d 


# Each subdirectory must supply rules for building sources it contributes
tests/%.o: ../tests/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


