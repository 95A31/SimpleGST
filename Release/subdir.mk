################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../ActivePoint.cpp \
../GeneralizedSuffixTree.cpp \
../Node.cpp \
../SimpleGST.cpp \
../Tasks.cpp 

OBJS += \
./ActivePoint.o \
./GeneralizedSuffixTree.o \
./Node.o \
./SimpleGST.o \
./Tasks.o 

CPP_DEPS += \
./ActivePoint.d \
./GeneralizedSuffixTree.d \
./Node.d \
./SimpleGST.d \
./Tasks.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -std=c++11 -fopenmp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


