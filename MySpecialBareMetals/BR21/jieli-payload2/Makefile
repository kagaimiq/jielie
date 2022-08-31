TARGET = AC6925E
OBJS = pre.o condet.o xprintf.o

CFLAGS  = -target pi32 -integrated-as -Werror -Os
ASFLAGS = -target pi32 -integrated-as -c
LDFLAGS = -Tlink.ld -lc

#for some reason these directories is not being put in the compilation flags
# so the libc stuff (-lc, string.h, etc) is not available
#JL_TOOLCHAIN_DIR = /home/kagaimiq/Desktop/JieLi/TOOLCAHN/pi32
JL_TOOLCHAIN_DIR = /x/Desktop/JieLi/TOOLCAHN/pi32
CFLAGS += -I"$(JL_TOOLCHAIN_DIR)/include/libc"
LDFLAGS += -L"$(JL_TOOLCHAIN_DIR)/libc"

#JL_TOOLCHAIN_BIN = wine $(JL_TOOLCHAIN_DIR)/bin/
JL_TOOLCHAIN_BIN = $(JL_TOOLCHAIN_DIR)/bin/

CC      = $(JL_TOOLCHAIN_BIN)clang
AS      = $(JL_TOOLCHAIN_BIN)clang
LD      = $(JL_TOOLCHAIN_BIN)pi32-ld
OBJDUMP = $(JL_TOOLCHAIN_BIN)llvm-objdump
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
