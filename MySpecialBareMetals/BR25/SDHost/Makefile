TARGET = JieLiKudasai

OBJS = \
	pre.o \
	mikosu.o \
	chan/ff.o \
	chan/ffunicode.o

CFLAGS  = -Werror -O2
ASFLAGS = -c
LDFLAGS = -Tlink.ld -lc

CFLAGS  += -I ../commoninc
LDFLAGS += -T ../commoninc/maskrom_stuff.ld

CFLAGS += -I ../commonsrc
OBJS += \
	../commonsrc/xprintf.o \
	../commonsrc/wallclk.o \
	../commonsrc/jl_irq.o

#------------------------------------------------------------------------

# You can get the toolchain from here: https://doc.zh-jieli.com/Tools/zh-cn/other_info/index.html
JL_TOOLCHAIN_DIR = ../../../../Toolchain/pi32v2

#for some reason these directories is not being put in the compilation flags
# so the libc stuff (-lc, string.h, etc) is not available
CFLAGS  += -I"$(JL_TOOLCHAIN_DIR)/include"
LDFLAGS += -L"$(JL_TOOLCHAIN_DIR)/lib"

JL_TOOLCHAIN_BIN = $(JL_TOOLCHAIN_DIR)/bin/
CC      = $(JL_TOOLCHAIN_BIN)cc
AS      = $(JL_TOOLCHAIN_BIN)cc
LD      = $(JL_TOOLCHAIN_BIN)lto-wrapper
OBJDUMP = $(JL_TOOLCHAIN_BIN)objdump
OBJCOPY = llvm-objcopy
SIZE    = llvm-size

all: $(TARGET).elf $(TARGET).bin

.PHONY: all clean

clean:
	rm -f $(OBJS)
	rm -f $(TARGET).elf
	rm -f $(TARGET).bin
	rm -f $(TARGET).lst

$(TARGET).elf: $(OBJS)
	$(LD) $(OBJS) -o $@ $(LDFLAGS)
	$(SIZE) -A $@
	$(OBJDUMP) -d $@ > $(TARGET).lst

$(TARGET).bin: $(TARGET).elf
	$(OBJCOPY) -O binary $< $@
