################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: GNU Compiler'
	"C:/ti/ccs1011/ccs/tools/compiler/msp430-gcc-9.2.0.50_win64/bin/msp430-elf-gcc-9.2.0.exe" -c -mmcu=msp430fr2433 -mhwmult=f5series -fno-exceptions -I"C:/ti/ccs1011/ccs/ccs_base/msp430/include_gcc" -I"C:/Users/steff/iCloudDrive/Trunk/CCS/Microtrait_Test" -I"C:/ti/ccs1011/ccs/tools/compiler/msp430-gcc-9.2.0.50_win64/msp430-elf/include" -O3 -funsigned-char -mtiny-printf -g -gdwarf-3 -gstrict-dwarf -Wall -Wextra -flto -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -std=c++17 -fno-rtti -fno-threadsafe-statics $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


