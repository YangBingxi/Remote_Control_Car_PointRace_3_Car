################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
delay/delay.obj: ../delay/delay.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"D:/Project_Program/Ccs_V7/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="F:/ProjectFile/ccs/PointRace_3_Car" --include_path="F:/ProjectFile/ccs/PointRace_3_Car/9.6'OLED" --include_path="F:/ProjectFile/ccs/PointRace_3_Car/delay" --include_path="F:/ProjectFile/ccs/PointRace_3_Car/key" --include_path="F:/ProjectFile/ccs/PointRace_3_Car/led" --include_path="F:/ProjectFile/ccs/PointRace_3_Car/Motor" --include_path="F:/ProjectFile/ccs/PointRace_3_Car/usart" --include_path="D:/ti/TivaWare_C_Series-2.1.4.178" --include_path="D:/Project_Program/Ccs_V7/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/include" --define=ccs="ccs" --define=PART_TM4C123GH6PM -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="delay/delay.d_raw" --obj_directory="delay" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


