.PHONY: test

test:
	@echo $(PATH)
	@echo $(INCLUDE)
	@echo $(LIB)
	@echo $(GCCLIB)

#
# File: Makefile
#
# Copyright (c) 2015 David Muriuki
# see the LICENCE file
#

# toolchain specific
TOOLCHAIN = arm-none-eabi-
CC = $(TOOLCHAIN)gcc
CXX = $(TOOLCHAIN)g++
# AS = $(TOOLCHAIN)gcc -x assembler-with-cpp
AS = $(TOOLCHAIN)as
LD = $(TOOLCHAIN)gcc
OBJCP = $(TOOLCHAIN)objcopy
AR = $(TOOLCHAIN)ar
GDB = $(TOOLCHAIN)gdb
GDBSERVER = /opt/openocd/bin/openocd -d 0 -c "interface osbdm" -f /opt/openocd/share/openocd/scripts/board/twr-k60n512.cfg
OPENOCDPID = $(shell pgrep openocd)

# application specific
CPU := cortex-m0plus
INSTRUCTION_MODE := thumb
TARGET := k32l2b3_smartlock
TARGET_EXT := elf
LD_SCRIPT := K32L2B31xxxxA_flash.ld

LIBS :=

# directories
INC_DIRS = aml aml/spi_aml aml/tmr_aml aml/wait_aml drivers source source/TML NfcLibrary NfcLibrary/inc NfcLibrary/NdefLibrary/inc NfcLibrary/NxpNci/inc device sf startup utilities board CMSIS CMSIS_driver component component/lists component/serial_manager component/uart ltc2941 .
SRC_DIRS := aml aml/spi_aml aml/tmr_aml aml/wait_aml drivers source source/TML NfcLibrary NfcLibrary/src NfcLibrary/NdefLibrary/src NfcLibrary/NxpNci/src device sf startup utilities board CMSIS CMSIS_driver component component/lists component/serial_manager component/uart ltc2941 . 
OUT_DIR := out
INC_DIRS_F = -I. $(patsubst %, -I%, $(INC_DIRS))

# add traling / if not empty
ifeq ($(strip $(OUT_DIR)), )
	OBJ_FOLDER =
else
	OBJ_FOLDER = $(strip $(OUT_DIR))/
endif

COMPILER_OPTIONS = -Os -g -Wall -fno-common -fdata-sections -ffreestanding -mapcs -std=gnu99 -ffunction-sections -fno-builtin -m$(INSTRUCTION_MODE) -mcpu=$(CPU) -MD -MP -mfloat-abi=soft -DCPU_K32L2B31VLH0A -DRW_SUPPORT=1 -D__USE_CMSIS -DNDEBUG -MMD -MP
ASSEMBLER_OPTIONS = -m$(INSTRUCTION_MODE) -mcpu=$(CPU) -MD -MP -mfloat-abi=soft -DCPU_K32L2B31VLH0A -DRW_SUPPORT=1 -D__USE_CMSIS -DNDEBUG -MMD -MP

DEPEND_OPTS = -MF $(OBJ_FOLDER)$(@F:.o=.d)

# Flags
#CFLAGS = $(COMPILER_OPTIONS) $(DEPEND_OPTS) $(INC_DIRS_F) -c
CFLAGS = $(COMPILER_OPTIONS) $(DEPEND_OPTS) $(INC_DIRS_F) -c
CXXFLAGS = $(COMPILER_OPTIONS) $(INC_DIRS_F) -c
ASFLAGS = $(ASSEMBLER_OPTIONS) $(INC_DIRS_F) -c
OBJCPFLAGS = -O ihex
ARFLAGS = cr

# Linker options
LD_OPTIONS = -Wl,-Map=$(OBJ_FOLDER)$(TARGET).map $(COMPILER_OPTIONS) -L ../ -T $(LD_SCRIPT) $(INC_DIRS_F)
LD_OPTIONS += -nostartfiles --specs=nano.specs --specs=nosys.specs

# RM := rm -rf
RM := del 

USER_OBJS :=
C_SRCS :=
S_SRCS :=
C_OBJS :=
S_OBJS :=

# All source/object files inside SRC_DIRS
C_SRCS := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))
C_OBJS := $(patsubst %.c,$(OBJ_FOLDER)%.o,$(notdir $(C_SRCS)))
S_SRCS := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.s))
S_OBJS := $(patsubst %.c,$(OBJ_FOLDER)%.o,$(notdir $(S_SRCS)))

VPATH := $(SRC_DIRS)

$(OBJ_FOLDER)%.o : %.s
	@echo 'Building file: $(@F)'
	@echo '--------------------'
	@echo 'Invoking: MCU Assembler'
	$(AS) $(ASFLAGS) $< -o $@
	@echo 'Finished building: $(@F)'
	@echo ' '

$(OBJ_FOLDER)%.o : %.c
	@echo 'Building file: $(@F)'
	@echo '--------------------'
	@echo 'Invoking: MCU C Compiler'
	$(CC) $(CFLAGS) $< -o $@
	@echo 'Finished building: $(@F)'
	@echo ' '

# TODO: generate assembly lisiting
debug: all
ifeq ($(OPENOCDPID), ) # start openocd if not already running
	$(GDBSERVER) &
	@echo "error: openocd server not running"
	exit()
endif
	$(GDB) -q -x .gdbcmds 
	 
all: clean create_outputdir $(OBJ_FOLDER)$(TARGET).$(TARGET_EXT) print_size

create_outputdir:
	$(shell mkdir $(OBJ_FOLDER) 2>/dev/null)

# Tool invocations
$(OBJ_FOLDER)$(TARGET).$(TARGET_EXT): $(C_OBJS) $(S_OBJS)
	@echo 'Building target: $@'
	@echo '-------------------'
	@echo 'Invoking: MCU Linker'
	$(LD) $(LD_OPTIONS) $(C_OBJS) $(S_OBJS) $(USER_OBJS) $(LIBS) -o $(OBJ_FOLDER)$(TARGET).$(TARGET_EXT)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	@echo 'Removing entire out directory'
	@echo '-----------------------------'
	#$(RM) $(TARGET).$(TARGET_EXT) $(TARGET).bin $(TARGET).map $(OBJ_FOLDER)*.* $(OBJ_FOLDER)
	$(RM) $(OBJ_FOLDER)*.* $(OBJ_FOLDER)
	@echo ' '

print_size:
	@echo 'Printing size'
	@echo '-------------'
	arm-none-eabi-size --totals $(OBJ_FOLDER)$(TARGET).$(TARGET_EXT); arm-none-eabi-objcopy -O binary $(OBJ_FOLDER)$(TARGET).$(TARGET_EXT) $(OBJ_FOLDER)$(TARGET).bin ;
	@echo ' '

.PHONY: all clean dependents print_size
