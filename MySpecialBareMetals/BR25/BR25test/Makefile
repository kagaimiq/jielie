TARGET = AC6965A

OBJS = \
	pre.o \
	mikosu.o \
	com/xprintf.o \
	com/wallclk.o \
	com/jl_irq.o

CFLAGS  = -Werror -O2
ASFLAGS = -c
LDFLAGS = -Tlink.ld -lc

CFLAGS += -I../commoninc
CFLAGS += -Icom

# You can get the toolchain from here: https://doc.zh-jieli.com/Tools/zh-cn/other_info/index.html
JL_TOOLCHAIN_DIR = /home/kagaimiq/Desktop/JieLi/TOOLCAHN/ws/pi32v2

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

all: $(TARGET) copy

.PHONY: all clean copy

clean:
	rm -f $(OBJS)
	rm -f $(TARGET)
	rm -f $(TARGET).lst
	rm -f $(TARGET).bin

$(TARGET): $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $@
	$(SIZE) -A $@
	$(OBJDUMP) -d $@ > $@.lst

copy: $(TARGET)
	$(OBJCOPY) -Obinary $< $<.bin
	sudo python3 ../../../../jl-uboot-tool/the-tool/jl_uboot_proto.py /dev/sg2 $<.bin
