################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../classes/Automata.c \
../classes/Derivation.c \
../classes/Derivations.c \
../classes/Grammar.c \
../classes/Production.c \
../classes/Productions.c \
../classes/Utils.c 

OBJS += \
./classes/Automata.o \
./classes/Derivation.o \
./classes/Derivations.o \
./classes/Grammar.o \
./classes/Production.o \
./classes/Productions.o \
./classes/Utils.o 

C_DEPS += \
./classes/Automata.d \
./classes/Derivation.d \
./classes/Derivations.d \
./classes/Grammar.d \
./classes/Production.d \
./classes/Productions.d \
./classes/Utils.d 


# Each subdirectory must supply rules for building sources it contributes
classes/%.o: ../classes/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


