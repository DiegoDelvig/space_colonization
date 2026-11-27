################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/draw.c \
../src/main.c \
../src/points.c \
../src/vec2.c 

C_DEPS += \
./src/draw.d \
./src/main.d \
./src/points.d \
./src/vec2.d 

OBJS += \
./src/draw.o \
./src/main.o \
./src/points.o \
./src/vec2.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I/usr/include/SDL2 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/draw.d ./src/draw.o ./src/main.d ./src/main.o ./src/points.d ./src/points.o ./src/vec2.d ./src/vec2.o

.PHONY: clean-src

