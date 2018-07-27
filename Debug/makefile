################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := D:/pro/TI/ccsv6/tools/compiler/c2000_6.2.5

ORDERED_OBJS += \
$(GEN_CMDS__FLAG) \
"./source/queue.obj" \
"./source/EX_i2c.obj" \
"./source/EX_data.obj" \
"./source/EX_31855.obj" \
"./source/EX.obj" \
"./source/DSP281x_usDelay.obj" \
"./source/DSP281x_SysCtrl.obj" \
"./source/DSP281x_Spi.obj" \
"./source/DSP281x_Sci.obj" \
"./source/DSP281x_PieVect.obj" \
"./source/DSP281x_PieCtrl.obj" \
"./source/DSP281x_MemCopy.obj" \
"./source/DSP281x_InitPeripherals.obj" \
"./source/DSP281x_Gpio.obj" \
"./source/DSP281x_GlobalVariableDefs.obj" \
"./source/DSP281x_Ev.obj" \
"./source/DSP281x_DefaultIsr.obj" \
"./source/DSP281x_CpuTimers.obj" \
"./source/DSP281x_CodeStartBranch.obj" \
"./source/DSP281x_Adc.obj" \
"./main.obj" \
"../cmd/DSP281x_Headers_nonBIOS.cmd" \
"../cmd/F2812_RAM_lnk.cmd" \
-l"libc.a" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include source/subdir_vars.mk
-include cmd/subdir_vars.mk
-include subdir_rules.mk
-include source/subdir_rules.mk
-include cmd/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
C2000_Code.out \

EXE_OUTPUTS__QUOTED += \
"C2000_Code.out" \

BIN_OUTPUTS += \
C2000_Code.hex \

BIN_OUTPUTS__QUOTED += \
"C2000_Code.hex" \


# All Target
all: C2000_Code.out

# Tool invocations
C2000_Code.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: C2000 Linker'
	"D:/pro/TI/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml -mt -g --diag_warning=225 --display_error_number --diag_wrap=off -z -m"C2000_Code.map" --stack_size=0x400 --warn_sections -i"D:/pro/TI/ccsv6/tools/compiler/c2000_6.2.5/lib" -i"../source" -i"D:/pro/TI/ccsv6/tools/compiler/c2000_6.2.5/include" -i"../include" --reread_libs --display_error_number --diag_wrap=off --xml_link_info="C2000_Code_linkInfo.xml" --rom_model -o "C2000_Code.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

C2000_Code.hex: $(EXE_OUTPUTS)
	@echo 'Invoking: C2000 Hex Utility'
	"D:/pro/TI/ccsv6/tools/compiler/c2000_6.2.5/bin/hex2000"  -o "C2000_Code.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXE_OUTPUTS__QUOTED)$(BIN_OUTPUTS__QUOTED)
	-$(RM) "main.pp" "source\DSP281x_Adc.pp" "source\DSP281x_CpuTimers.pp" "source\DSP281x_DefaultIsr.pp" "source\DSP281x_Ev.pp" "source\DSP281x_GlobalVariableDefs.pp" "source\DSP281x_Gpio.pp" "source\DSP281x_InitPeripherals.pp" "source\DSP281x_MemCopy.pp" "source\DSP281x_PieCtrl.pp" "source\DSP281x_PieVect.pp" "source\DSP281x_Sci.pp" "source\DSP281x_Spi.pp" "source\DSP281x_SysCtrl.pp" "source\EX.pp" "source\EX_31855.pp" "source\EX_data.pp" "source\EX_i2c.pp" "source\queue.pp" 
	-$(RM) "main.obj" "source\DSP281x_Adc.obj" "source\DSP281x_CodeStartBranch.obj" "source\DSP281x_CpuTimers.obj" "source\DSP281x_DefaultIsr.obj" "source\DSP281x_Ev.obj" "source\DSP281x_GlobalVariableDefs.obj" "source\DSP281x_Gpio.obj" "source\DSP281x_InitPeripherals.obj" "source\DSP281x_MemCopy.obj" "source\DSP281x_PieCtrl.obj" "source\DSP281x_PieVect.obj" "source\DSP281x_Sci.obj" "source\DSP281x_Spi.obj" "source\DSP281x_SysCtrl.obj" "source\DSP281x_usDelay.obj" "source\EX.obj" "source\EX_31855.obj" "source\EX_data.obj" "source\EX_i2c.obj" "source\queue.obj" 
	-$(RM) "source\DSP281x_CodeStartBranch.pp" "source\DSP281x_usDelay.pp" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

