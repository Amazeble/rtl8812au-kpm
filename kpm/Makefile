ifndef TARGET_COMPILE
$(error TARGET_COMPILE not set)
endif

ifndef KP_DIR
KP_DIR := ../KernelPatch
endif

CC := $(TARGET_COMPILE)gcc

# These are the include directories used by the current
# KernelPatch demo-hello Makefile.
INCLUDE_DIRS := \
	. \
	include \
	$(KP_DIR)/kernel/include \
	$(KP_DIR)/kernel/patch/include \
	$(KP_DIR)/kernel/linux/include \
	$(KP_DIR)/kernel/linux/arch/arm64/include \
	$(KP_DIR)/kernel/linux/tools/arch/arm64/include

INCLUDE_FLAGS := \
	$(foreach dir,$(INCLUDE_DIRS),-I$(dir))

CFLAGS := \
	-O2 \
	-g \
	-fno-builtin \
	-fno-PIC \
	-fno-pic \
	-fno-plt \
	-fno-stack-protector \
	-fno-asynchronous-unwind-tables \
	-ffreestanding \
	$(INCLUDE_FLAGS)

OBJS := \
	main.o \
	rtl8812au.o

TARGET := rtl8812au.kpm

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -r -o $@ $^

main.o: main.c include/rtl8812au_kpm.h
	$(CC) $(CFLAGS) \
		-Trtl8812au.lds \
		-c \
		-O2 \
		-o $@ \
		$<

rtl8812au.o: rtl8812au.c include/rtl8812au_kpm.h
	$(CC) $(CFLAGS) \
		-Trtl8812au.lds \
		-c \
		-O2 \
		-o $@ \
		$<

clean:
	rm -f \
		*.o \
		*.kpm \
		*.map

.PHONY: all clean