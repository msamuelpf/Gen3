################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../Source/Buzzer.c \
../Source/Communications.c \
../Source/CycleSelector.c \
../Source/Display.c \
../Source/Drv_Adc.c \
../Source/Drv_Tmr0.c \
../Source/Drv_TmrInterrupt00.c \
../Source/Drv_TmrInterrupt03.c \
../Source/Drv_TmrPwm07.c \
../Source/Drv_UART1.c \
../Source/Hardware.c \
../Source/InitMCU.c \
../Source/Main.c \
../Source/MainProcess.c \
../Source/RAM.c \
../Source/Tablas.c \
../Source/Test.c \
../Source/crc.c 

COMPILER_OBJS += \
Source/Buzzer.obj \
Source/Communications.obj \
Source/CycleSelector.obj \
Source/Display.obj \
Source/Drv_Adc.obj \
Source/Drv_Tmr0.obj \
Source/Drv_TmrInterrupt00.obj \
Source/Drv_TmrInterrupt03.obj \
Source/Drv_TmrPwm07.obj \
Source/Drv_UART1.obj \
Source/Hardware.obj \
Source/InitMCU.obj \
Source/Main.obj \
Source/MainProcess.obj \
Source/RAM.obj \
Source/Tablas.obj \
Source/Test.obj \
Source/crc.obj 

C_DEPS += \
Source/Buzzer.d \
Source/Communications.d \
Source/CycleSelector.d \
Source/Display.d \
Source/Drv_Adc.d \
Source/Drv_Tmr0.d \
Source/Drv_TmrInterrupt00.d \
Source/Drv_TmrInterrupt03.d \
Source/Drv_TmrPwm07.d \
Source/Drv_UART1.d \
Source/Hardware.d \
Source/InitMCU.d \
Source/Main.d \
Source/MainProcess.d \
Source/RAM.d \
Source/Tablas.d \
Source/Test.d \
Source/crc.d 

# Each subdirectory must supply rules for building sources it contributes
Source/%.obj: ../Source/%.c 
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	@echo Source\cDepSubCommand.tmp=
	@sed -e "s/^/ /" "Source\cDepSubCommand.tmp"
	ccrl -subcommand="Source\cDepSubCommand.tmp" -o "$(@:%.obj=%.d)"  -MT="$(@:%.obj=%.obj)"  -MT="$(@:%.obj=%.d)" -msg_lang=english "$<"
	@echo Source\cSubCommand.tmp=
	@sed -e "s/^/ /" "Source\cSubCommand.tmp"
	ccrl -subcommand="Source\cSubCommand.tmp" -msg_lang=english -o "$(@:%.d=%.obj)" "$<"
	@echo 'Finished Scanning and building: $<'
	@echo.

