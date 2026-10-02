ifndef TARGET_COMPILE
$(error TARGET_COMPILE is not set)
endif

ifndef KP_DIR
KP_DIR := ../KernelPatch
endif

ifndef DRIVER_DIR
DRIVER_DIR := ../rtl8812au
endif

CC := $(TARGET_COMPILE)gcc
LD := $(TARGET_COMPILE)ld
OBJCOPY := $(TARGET_COMPILE)objcopy
READELF := $(TARGET_COMPILE)readelf

INCLUDE_DIRS := \
	. \
	include \
	$(KP_DIR)/kernel/include \
	$(KP_DIR)/kernel/patch/include \
	$(KP_DIR)/kernel/include/asm-generic \
	$(KP_DIR)/kernel/arch/arm64/include \
	$(KP_DIR)/kernel/tools/arch/arm64/include

INCLUDE_FLAGS := \
	$(foreach dir,$(INCLUDE_DIRS),-I$(dir))

CFLAGS := \
	-O2 \
	-g \
	-fno-builtin \
	-fno-stack-protector \
	-fno-asynchronous-unwind-tables \
	-fno-unwind-tables \
	-fno-pic \
	-fno-plt \
	-mstrict-align \
	-ffreestanding \
	$(INCLUDE_FLAGS)

LDFLAGS := \
	-r

OBJS := \
	main.o \
	symbols.o \
	compat.o

TARGET := rtl8812au.kpm

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) \
		-o $@ \
		$^
	
main.o: main.c
	$(CC) $(CFLAGS) \
		-Trtl8812au.lds \
		-c $< \
		-o $@

symbols.o: symbols.c
	$(CC) $(CFLAGS) \
		-c $< \
		-o $@

compat.o: compat.c
	$(CC) $(CFLAGS) \
		-c $< \
		-o $@

clean:
	rm -f \
		*.o \
		*.kpm \
		*.map

.PHONY: all clean