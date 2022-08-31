TARGET = AC6925E
OBJS = \
	pre.o \
	condet.o \
	com/xprintf.o \
	com/jl_irtc.o \
	chan/ff.o

CFLAGS  = -target pi32 -integrated-as -Werror -O2
ASFLAGS = -target pi32 -integrated-as -c
LDFLAGS = -Tlink.ld -lc

CFLAGS += -Icom -Ichan

#for some reason these directories is not being put in the compilation flags
# so the libc stuff (-lc, string.h, etc) is not available
JL_TOOLCHAIN_DIR = /home/kagaimiq/Desktop/JieLi/TOOLCAHN/ws/pi32
CFLAGS += -I"$(JL_TOOLCHAIN_DIR)/include"
LDFLAGS += -L"$(JL_TOOLCHAIN_DIR)/lib"

JL_TOOLCHAIN_BIN = $(JL_TOOLCHAIN_DIR)/bin/

CC      = $(JL_TOOLCHAIN_BIN)clang
AS      = $(JL_TOOLCHAIN_BIN)clang
LD      = $(JL_TOOLCHAIN_BIN)lto-wrapper
OBJDUMP = $(JL_TOOLCHAIN_BIN)objdump
OBJCOPY = llvm-objcopy
SIZE    = llvm-size

all: $(TARGET) copy

clean:
	rm -f $(OBJS)
	rm -f $(TARGET)
	rm -f $(TARGET).bin
	rm -f $(TARGET).lst

$(TARGET): $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $@
	$(SIZE) -A $@

copy: $(TARGET)
	$(OBJDUMP) -d $< > $<.lst
	$(OBJCOPY) -Obinary $< $<.bin
	cp $<.bin ../payload.bin
