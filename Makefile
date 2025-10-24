CC := i686-elf-gcc
CPPFLAGS := -Iinclude
CFLAGS := -std=c17 -ffreestanding -O2 -Wall -Wextra -g
LDFLAGS := -T src/kernel.ld -ffreestanding -O2 -nostdlib -lgcc -g

QEMU32 := qemu-system-i386
QEMUFLAGS := -m 4G -cdrom risx.iso
QEMUDEBUGFLAGS := -s -S -monitor stdio

S_SRCS := $(wildcard src/*.S)
C_SRCS := $(wildcard src/*.c)

SRCS := $(S_SRCS) $(C_SRCS)
OBJ_DIR := target/i686

OBJS := $(patsubst src/%, $(OBJ_DIR)/%, $(SRCS:.S=.o))
OBJS := $(patsubst src/%, $(OBJ_DIR)/%, $(OBJS:.c=.o))

.PHONY: all clean check qemu qemu-debug
all: risx.elf32

risx.iso: risx.elf32 config/grub/grub.cfg
	@mkdir -p iso/boot/grub
	@cp config/grub/grub.cfg iso/boot/grub/grub.cfg
	@cp $(OBJ_DIR)/risx.elf32 iso/boot/risx.elf32
	@grub-mkrescue -o risx.iso iso \
		&& echo "ISO OK" \
		|| echo "ISO FAILED"

risx.elf32: $(OBJS) src/kernel.ld
	@mkdir -p $(OBJ_DIR)
	$(CC) $(OBJS) $(LDFLAGS) -o $(OBJ_DIR)/risx.elf32

$(OBJ_DIR)/%.o: src/%.S
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

clean:
	@rm -rf target/i686 iso/boot risx.iso

check: risx.elf32
	@grub-file --is-x86-multiboot2 $(OBJ_DIR)/risx.elf32 \
		&& echo "MULTIBOOT2 OK" \
		|| echo "MULTIBOOT2 NONCOMPLIANT"

qemu: risx.iso
	@$(QEMU32) $(QEMUFLAGS)

qemu-debug: risx.iso
	@$(QEMU32) $(QEMUFLAGS) $(QEMUDEBUGFLAGS)
