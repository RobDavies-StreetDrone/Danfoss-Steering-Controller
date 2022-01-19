################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Generated_Code/ADC0.c" \
"../Generated_Code/CAN1.c" \
"../Generated_Code/Cpu.c" \
"../Generated_Code/EN1.c" \
"../Generated_Code/IO_Map.c" \
"../Generated_Code/PWM1.c" \
"../Generated_Code/PWM2.c" \
"../Generated_Code/SW1.c" \
"../Generated_Code/SW2.c" \
"../Generated_Code/TI1.c" \
"../Generated_Code/Vectors.c" \

C_SRCS += \
../Generated_Code/ADC0.c \
../Generated_Code/CAN1.c \
../Generated_Code/Cpu.c \
../Generated_Code/EN1.c \
../Generated_Code/IO_Map.c \
../Generated_Code/PWM1.c \
../Generated_Code/PWM2.c \
../Generated_Code/SW1.c \
../Generated_Code/SW2.c \
../Generated_Code/TI1.c \
../Generated_Code/Vectors.c \

OBJS += \
./Generated_Code/ADC0_c.obj \
./Generated_Code/CAN1_c.obj \
./Generated_Code/Cpu_c.obj \
./Generated_Code/EN1_c.obj \
./Generated_Code/IO_Map_c.obj \
./Generated_Code/PWM1_c.obj \
./Generated_Code/PWM2_c.obj \
./Generated_Code/SW1_c.obj \
./Generated_Code/SW2_c.obj \
./Generated_Code/TI1_c.obj \
./Generated_Code/Vectors_c.obj \

OBJS_QUOTED += \
"./Generated_Code/ADC0_c.obj" \
"./Generated_Code/CAN1_c.obj" \
"./Generated_Code/Cpu_c.obj" \
"./Generated_Code/EN1_c.obj" \
"./Generated_Code/IO_Map_c.obj" \
"./Generated_Code/PWM1_c.obj" \
"./Generated_Code/PWM2_c.obj" \
"./Generated_Code/SW1_c.obj" \
"./Generated_Code/SW2_c.obj" \
"./Generated_Code/TI1_c.obj" \
"./Generated_Code/Vectors_c.obj" \

C_DEPS += \
./Generated_Code/ADC0_c.d \
./Generated_Code/CAN1_c.d \
./Generated_Code/Cpu_c.d \
./Generated_Code/EN1_c.d \
./Generated_Code/IO_Map_c.d \
./Generated_Code/PWM1_c.d \
./Generated_Code/PWM2_c.d \
./Generated_Code/SW1_c.d \
./Generated_Code/SW2_c.d \
./Generated_Code/TI1_c.d \
./Generated_Code/Vectors_c.d \

C_DEPS_QUOTED += \
"./Generated_Code/ADC0_c.d" \
"./Generated_Code/CAN1_c.d" \
"./Generated_Code/Cpu_c.d" \
"./Generated_Code/EN1_c.d" \
"./Generated_Code/IO_Map_c.d" \
"./Generated_Code/PWM1_c.d" \
"./Generated_Code/PWM2_c.d" \
"./Generated_Code/SW1_c.d" \
"./Generated_Code/SW2_c.d" \
"./Generated_Code/TI1_c.d" \
"./Generated_Code/Vectors_c.d" \

OBJS_OS_FORMAT += \
./Generated_Code/ADC0_c.obj \
./Generated_Code/CAN1_c.obj \
./Generated_Code/Cpu_c.obj \
./Generated_Code/EN1_c.obj \
./Generated_Code/IO_Map_c.obj \
./Generated_Code/PWM1_c.obj \
./Generated_Code/PWM2_c.obj \
./Generated_Code/SW1_c.obj \
./Generated_Code/SW2_c.obj \
./Generated_Code/TI1_c.obj \
./Generated_Code/Vectors_c.obj \


# Each subdirectory must supply rules for building sources it contributes
Generated_Code/ADC0_c.obj: ../Generated_Code/ADC0.c
	@echo 'Building file: $<'
	@echo 'Executing target #7 $<'
	@echo 'Invoking: S12Z Compiler'
	"$(S12Z_ToolsDirEnv)/mwccs12lisa" -c @@"Generated_Code/ADC0.args" -o "Generated_Code/ADC0_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/%.d: ../Generated_Code/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Generated_Code/CAN1_c.obj: ../Generated_Code/CAN1.c
	@echo 'Building file: $<'
	@echo 'Executing target #8 $<'
	@echo 'Invoking: S12Z Compiler'
	"$(S12Z_ToolsDirEnv)/mwccs12lisa" -c @@"Generated_Code/CAN1.args" -o "Generated_Code/CAN1_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/Cpu_c.obj: ../Generated_Code/Cpu.c
	@echo 'Building file: $<'
	@echo 'Executing target #9 $<'
	@echo 'Invoking: S12Z Compiler'
	"$(S12Z_ToolsDirEnv)/mwccs12lisa" -c @@"Generated_Code/Cpu.args" -o "Generated_Code/Cpu_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/EN1_c.obj: ../Generated_Code/EN1.c
	@echo 'Building file: $<'
	@echo 'Executing target #10 $<'
	@echo 'Invoking: S12Z Compiler'
	"$(S12Z_ToolsDirEnv)/mwccs12lisa" -c @@"Generated_Code/EN1.args" -o "Generated_Code/EN1_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/IO_Map_c.obj: ../Generated_Code/IO_Map.c
	@echo 'Building file: $<'
	@echo 'Executing target #11 $<'
	@echo 'Invoking: S12Z Compiler'
	"$(S12Z_ToolsDirEnv)/mwccs12lisa" -c @@"Generated_Code/IO_Map.args" -o "Generated_Code/IO_Map_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/PWM1_c.obj: ../Generated_Code/PWM1.c
	@echo 'Building file: $<'
	@echo 'Executing target #12 $<'
	@echo 'Invoking: S12Z Compiler'
	"$(S12Z_ToolsDirEnv)/mwccs12lisa" -c @@"Generated_Code/PWM1.args" -o "Generated_Code/PWM1_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/PWM2_c.obj: ../Generated_Code/PWM2.c
	@echo 'Building file: $<'
	@echo 'Executing target #13 $<'
	@echo 'Invoking: S12Z Compiler'
	"$(S12Z_ToolsDirEnv)/mwccs12lisa" -c @@"Generated_Code/PWM2.args" -o "Generated_Code/PWM2_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/SW1_c.obj: ../Generated_Code/SW1.c
	@echo 'Building file: $<'
	@echo 'Executing target #14 $<'
	@echo 'Invoking: S12Z Compiler'
	"$(S12Z_ToolsDirEnv)/mwccs12lisa" -c @@"Generated_Code/SW1.args" -o "Generated_Code/SW1_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/SW2_c.obj: ../Generated_Code/SW2.c
	@echo 'Building file: $<'
	@echo 'Executing target #15 $<'
	@echo 'Invoking: S12Z Compiler'
	"$(S12Z_ToolsDirEnv)/mwccs12lisa" -c @@"Generated_Code/SW2.args" -o "Generated_Code/SW2_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/TI1_c.obj: ../Generated_Code/TI1.c
	@echo 'Building file: $<'
	@echo 'Executing target #16 $<'
	@echo 'Invoking: S12Z Compiler'
	"$(S12Z_ToolsDirEnv)/mwccs12lisa" -c @@"Generated_Code/TI1.args" -o "Generated_Code/TI1_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/Vectors_c.obj: ../Generated_Code/Vectors.c
	@echo 'Building file: $<'
	@echo 'Executing target #17 $<'
	@echo 'Invoking: S12Z Compiler'
	"$(S12Z_ToolsDirEnv)/mwccs12lisa" -c @@"Generated_Code/Vectors.args" -o "Generated_Code/Vectors_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '


