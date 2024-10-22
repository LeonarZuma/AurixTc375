# Project name
TARGET = Test
# Application source files to compile
SRCS  = Cpu0_Main.c Cpu1_Main.c Cpu2_Main.c Bsp.c Assert.c sync_on_halt.c
SRCS += Button.c Led.c
SRCS += Buffer.c Queue.c Scheduler.c Phase1.c RTCC.c
SRCS += Leds.c Mouse.c Can_Task.c AppSerial.c
SRCS += CompilerGcc.c CompilerDcc.c CompilerGhs.c CompilerGnuc.c CompilerTasking.c 
SRCS += Ifx_Ssw_Infra.c Ifx_Ssw_Tc0.c Ifx_Ssw_Tc1.c Ifx_Ssw_Tc2.c Ifx_Cfg_Ssw.c Ifx_Cfg_SswBmhd.c
SRCS += IfxPmsEvr.c IfxPmsPm.c IfxPms_PinMap.c
SRCS += IfxScuCcu.c IfxScuEru.c IfxScuLbist.c IfxScuRcu.c IfxScuWdt.c IfxScu_PinMap.c IfxScu_cfg.c
SRCS += IfxCpu.c IfxCpu_Irq.c IfxCpu_Trap.c IfxCpu_cfg.c
SRCS += IfxPort.c IfxPort_Io.c IfxPort_PinMap.c IfxPort_cfg.c
SRCS += IfxStm.c IfxStm_cfg.c IfxSrc.c
SRCS += IfxCan_Can.c IfxCan.c IfxCan_PinMap.c IfxCan_cfg.c

# Linker file
LINKER = Lcf_Gnuc_Tricore_Tc.lsl
# Global symbols
SYMBOLS  = 

# Directories with source files (.c y .s)
SRC_PATHS  = Configurations .
SRC_PATHS += Driver
SRC_PATHS += HL_Driver
SRC_PATHS += Application
SRC_PATHS += Configurations/Debug
SRC_PATHS += Libraries/iLLD/TC37A/Tricore/_Impl
SRC_PATHS += Libraries/iLLD/TC37A/Tricore/_PinMap
SRC_PATHS += Libraries/iLLD/TC37A/Tricore/_Lib/DataHandling
SRC_PATHS += Libraries/iLLD/TC37A/Tricore/_Lib/InternalMux
SRC_PATHS += Libraries/iLLD/TC37A/Tricore/Cpu/Irq
SRC_PATHS += Libraries/iLLD/TC37A/Tricore/Cpu/Std
SRC_PATHS += Libraries/iLLD/TC37A/Tricore/Cpu/Trap
SRC_PATHS += Libraries/Infra/Platform/Tricore/Compilers
SRC_PATHS += Libraries/Infra/Ssw/TC37A/Tricore
SRC_PATHS += Libraries/Service/CpuGeneric/If
SRC_PATHS += Libraries/Service/CpuGeneric/StdIf
SRC_PATHS += Libraries/Service/CpuGeneric/SysSe/Bsp
SRC_PATHS += Libraries/Service/CpuGeneric/SysSe/Comm
SRC_PATHS += Libraries/Service/CpuGeneric/SysSe/General
SRC_PATHS += Libraries/Service/CpuGeneric/SysSe/Math
SRC_PATHS += Libraries/Service/CpuGeneric/SysSe/Time
SRC_PATHS += Libraries/iLLD/TC37A/Tricore/Scu
SRC_PATHS += Libraries/iLLD/TC37A/Tricore/Scu/Std
SRC_PATHS += Libraries/iLLD/TC37A/Tricore/Port
SRC_PATHS += Libraries/iLLD/TC37A/Tricore/Port/Io
SRC_PATHS += Libraries/iLLD/TC37A/Tricore/Port/Std
SRC_PATHS += Libraries/iLLD/TC37A/Tricore/Pms/Std
SRC_PATHS += Libraries/iLLD/TC37A/Tricore/Stm/Std
SRC_PATHS += Libraries/iLLD/TC37A/Tricore/Src
SRC_PATHS += Libraries/iLLD/TC37A/Tricore/Src/Std
SRC_PATHS += Libraries/iLLD/TC37A/Tricore/Can
SRC_PATHS += Libraries/iLLD/TC37A/Tricore/Can/Std
SRC_PATHS += Libraries/iLLD/TC37A/Tricore/Can/Can


# Directories with header files (.c y .s)
INC_PATHS  = Configurations
INC_PATHS += Driver
INC_PATHS += HL_Driver
INC_PATHS += Application
INC_PATHS += Libraries
INC_PATHS += Libraries/iLLD/TC37A/Tricore
INC_PATHS += Libraries/iLLD/TC37A/Tricore/_Impl
INC_PATHS += Libraries/iLLD/TC37A/Tricore/_PinMap
INC_PATHS += Libraries/iLLD/TC37A/Tricore/_Lib/DataHandling
INC_PATHS += Libraries/iLLD/TC37A/Tricore/_Lib/InternalMux
INC_PATHS += Libraries/iLLD/TC37A/Tricore/Cpu/Irq
INC_PATHS += Libraries/iLLD/TC37A/Tricore/Cpu/Std
INC_PATHS += Libraries/iLLD/TC37A/Tricore/Cpu/Trap
INC_PATHS += Libraries/Infra
INC_PATHS += Libraries/Infra/Platform
INC_PATHS += Libraries/Infra/Platform/Tricore
INC_PATHS += Libraries/Infra/Platform/Tricore/Compilers
INC_PATHS += Libraries/Infra/Sfr
INC_PATHS += Libraries/Infra/Sfr/TC37A
INC_PATHS += Libraries/Infra/Sfr/TC37A/_Reg
INC_PATHS += Libraries/Infra/Ssw
INC_PATHS += Libraries/Infra/Ssw/TC37A
INC_PATHS += Libraries/Infra/Ssw/TC37A/Tricore
INC_PATHS += Libraries/Service
INC_PATHS += Libraries/Service/CpuGeneric
INC_PATHS += Libraries/Service/CpuGeneric/_Utilities
INC_PATHS += Libraries/Service/CpuGeneric/If
INC_PATHS += Libraries/Service/CpuGeneric/If/Ccu6If
INC_PATHS += Libraries/Service/CpuGeneric/StdIf
INC_PATHS += Libraries/Service/CpuGeneric/SysSe/Bsp
INC_PATHS += Libraries/Service/CpuGeneric/SysSe/Comm
INC_PATHS += Libraries/Service/CpuGeneric/SysSe/General
INC_PATHS += Libraries/Service/CpuGeneric/SysSe/Math
INC_PATHS += Libraries/Service/CpuGeneric/SysSe/Time
INC_PATHS += Libraries/iLLD/TC37A/Tricore/Scu
INC_PATHS += Libraries/iLLD/TC37A/Tricore/Scu/Std
INC_PATHS += Libraries/iLLD/TC37A/Tricore/Port
INC_PATHS += Libraries/iLLD/TC37A/Tricore/Port/Io
INC_PATHS += Libraries/iLLD/TC37A/Tricore/Port/Std
INC_PATHS += Libraries/iLLD/TC37A/Tricore/Pms/Std
INC_PATHS += Libraries/iLLD/TC37A/Tricore/Scu/Std
INC_PATHS += Libraries/iLLD/TC37A/Tricore/Stm/Std
INC_PATHS += Libraries/iLLD/TC37A/Tricore/Src
INC_PATHS += Libraries/iLLD/TC37A/Tricore/Src/Std
INC_PATHS += Libraries/iLLD/TC37A/Tricore/Can
INC_PATHS += Libraries/iLLD/TC37A/Tricore/Can/Std
INC_PATHS += Libraries/iLLD/TC37A/Tricore/Can/Can


CPU = -mtc162

# Compilation options
CFLAGS  = $(CPU)
CFLAGS += -O0                       # Compile with Size Optimizations (O0, O1, O2, O3, Os)
CFLAGS += -ggdb3                    # Debugging information level (g1, g2, g3)
CFLAGS += -std=c99                  # Comply with C11
CFLAGS += -Wall                     # Be anal Enable All Warnings
CFLAGS += -Wstrict-prototypes       # Warn if a function is declared or defined without specifying the argument types
CFLAGS += -Wsign-compare            # Warn when a comparison between signed and unsigned values could produce an incorrect result when the signed value is converted to unsigned.
CFLAGS += -fmessage-length=0
CFLAGS += -fno-common               # In C code, controls the placement of uninitialized global variables.
CFLAGS += -fstrict-volatile-bitfields 
CFLAGS += -fdata-sections 			# Create a separate data section
CFLAGS += -ffunction-sections 		# Create a separate function section
CFLAGS += -funsigned-bitfields 		# Bitfields are always unsigned
CFLAGS += -fstack-usage 			# Emits stack usage information for the program, on a per-function basis, when compiling with -g or -gline-tables-only. The option -fstack-usage is enabled by default.
CFLAGS += -fdump-ipa-all 			# Dump all interprocedural optimization passes and their results.
CFLAGS += -fdiagnostics-color=always # color the output
CFLAGS += -fomit-frame-pointer      # Don't keep the frame pointer in a register for functions that don't need one
CFLAGS += -fverbose-asm             # Put extra commentary information in the generated assembly code

#opciones de linker
LFLAGS  = $(CPU)
LFLAGS += -nocrt0 						# do not use the standard system startup files when linking
LFLAGS += -Wl,--gc-sections				# Remove unused sections
LFLAGS += -Wl,-Map=Build/$(TARGET).map	# Generate map file

# Prefix substiotution
OBJS = $(SRCS:%.c=Build/obj/%.o)
DEPS = $(OBJS:%.o=%.d)


VPATH = $(SRC_PATHS)
INCLS = $(addprefix -I ,$(INC_PATHS))

#---Build instructions
all : build $(TARGET)

$(TARGET) : $(addprefix Build/, $(TARGET).elf)
	tricore-objcopy -Oihex $< Build/$(TARGET).hex
	tricore-objdump -S $< > Build/$(TARGET).lst
	tricore-size --format=berkeley $<

Build/$(TARGET).elf : $(OBJS)
	tricore-gcc $(LFLAGS) -T $(LINKER) -o $@ $^

Build/obj/%.o : %.c
	tricore-gcc $(CFLAGS) $(INCLS) $(SYMBOLS) -o $@ -c $<

Build/obj/%.o : %.s
	tricore-gcc $(AFLAGS) $(SYMBOLS) -o $@ -c $<

-include $(DEPS)

#---Create the build directories
.PHONY : build
build :
	mkdir -p Build/obj

#---Remove the compilation build files
.PHONY : clean
clean :
	rm -rf Build
