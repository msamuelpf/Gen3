################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include makefile.init

RM := rm -rf *.sni *.dbg *.lst *.lis *.lpp *.map *.x *.lbp *.h *.bls *.libelf *.rel *.lbk *.abs *.prn *.mi *.fsy *.ud *.udm 1st/*.abs 1st/*.fsy

# All of the sources participating in the build are defined here
-include sources.mk
-include generate/subdir.mk
-include Source/subdir.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif 
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif 
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif 
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif 
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif 
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif 
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif 
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif 
ifneq ($(strip $(SX_DEPS)),)
-include $(SX_DEPS)
endif 
ifneq ($(strip $(JMP_DEPS)),)
-include $(JMP_DEPS)
endif 
ifneq ($(strip $(SRC_DEPS)),)
-include $(SRC_DEPS)
endif 
ifneq ($(strip $(PP_DEPS)),)
-include $(PP_DEPS)
endif 
ifneq ($(strip $(P_DEPS)),)
-include $(P_DEPS)
endif 
ifneq ($(strip $(FSY_DEPS)),)
-include $(FSY_DEPS)
endif 
endif

ifneq ($(strip $(SRC_UPPER_SRCS)),)
ALL_ASMS += $(SRC_UPPER_SRCS) 
endif
ifneq ($(strip $(SRC_SRCS)),)
ALL_ASMS += $(SRC_SRCS) 
endif
ifneq ($(strip $(S_UPPER_SRCS)),)
ALL_ASMS += $(S_UPPER_SRCS) 
endif
ifneq ($(strip $(S_SRCS)),)
ALL_ASMS += $(S_SRCS) 
endif


-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables
LINKER_OUTPUT_OUTPUTS += \
Test.abs

CONVERTOR_OUTPUT_OUTPUTS += \
Test.mot

OBJS := \
$(COMPILER_OBJS) \
$(INDIVIDUAL_COMPILER_OBJS) \
$(ASSEMBLER_OBJS) \
$(CUSTOM_OBJS)


# All Target
all: $(CONVERTOR_OUTPUT_OUTPUTS) Test.x Test.udm

	@echo 'Build complete.'

Test.mot: $(LINKER_OUTPUT_OUTPUTS) 
	@echo 'Invoking: Converter'
	@echo 'Building target:'
	@echo ConverterTest.tmp=
	@sed -e "s/^/    /" "ConverterTest.tmp"
	rlink "Test.abs" -subcommand="ConverterTest.tmp"
	@echo 'Finished building target:'
	@echo.


Test.abs: $(OBJS)  $(ALL_ASMS)
	@echo 'Invoking: Linker'
	@echo LinkerTest.tmp=
	@sed -e "s/^/    /" "LinkerTest.tmp"
	rlink -subcommand="LinkerTest.tmp"
	@echo 'Finished building:'
	@echo.


Test.x: Test.abs
		-C:\Users\LDCMEXDI\.eclipse\com.renesas.platform_1401425906\Utilities\\ccrl\renesas_cc_converter.exe Test.abs Test.x

Test.udm: $(LINKER_OUTPUT_OUTPUTS) $(CONVERTOR_OUTPUT_OUTPUTS)
	udcollector -subcommand=udSubcommand.tmp -output=Test.udm

# Other Targets
clean:
	-$(RM) $(LINKER_OUTPUT_OUTPUTS) $(CONVERTOR_OUTPUT_OUTPUTS)
	-rm -rf $(OBJS) $(C_DEPS) $(ASM_DEPS) $(DSP_DEPS) 
	-rm -rf generate/*.asm generate/*.p generate/*.pp generate/*.src generate/*.jmp generate/*.lst generate/*.prn generate/*.i generate/*.ud 
	-rm -rf Source/*.asm Source/*.p Source/*.pp Source/*.src Source/*.jmp Source/*.lst Source/*.prn Source/*.i Source/*.ud 
	@echo
	@echo 'Clean complete.'

.PHONY: all clean 
-include ../makefile.targets