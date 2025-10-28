CC := i686-elf-gcc
CPPFLAGS := -Iinclude -I../libk/include
CFLAGS := -std=c17 -ffreestanding -O2 -Wall -Wextra -g
LDFLAGS := -T src/kernel.ld -ffreestanding -O2 -nostdlib -lgcc -g

QEMU32 := qemu-system-i386
QEMUFLAGS := -m 4G -cdrom risx.iso
QEMUDEBUGFLAGS := -s -S -monitor stdio

S_SRCS := $(shell find src -name '*.S')
C_SRCS := $(shell find src -name '*.c')

SRCS := $(S_SRCS) $(C_SRCS)
OBJ_DIR := target

OBJS := $(S_SRCS:src/%.S=$(OBJ_DIR)/%.o) $(C_SRCS:src/%.c=$(OBJ_DIR)/%.o)

.PHONY: all clean check qemu qemu-debug
all: $(OBJ_DIR)/risx.elf32

risx.iso: $(OBJ_DIR)/risx.elf32 config/grub/grub.cfg
	@mkdir -p $(OBJ_DIR)/iso/boot/grub
	@cp config/grub/grub.cfg $(OBJ_DIR)/iso/boot/grub/grub.cfg
	@cp $(OBJ_DIR)/risx.elf32 $(OBJ_DIR)/iso/boot/risx.elf32
	@grub-mkrescue -o risx.iso $(OBJ_DIR)/iso \
		&& echo "ISO OK" \
		|| echo "ISO FAILED"

$(OBJ_DIR)/risx.elf32: $(OBJS) src/kernel.ld
	@mkdir -p $(OBJ_DIR)
	$(CC) $(OBJS) $(LDFLAGS) -o $(OBJ_DIR)/risx.elf32

$(OBJ_DIR)/%.o: src/%.S
	@mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

clean:
	@rm -rf target risx.iso

check: $(OBJ_DIR)/risx.elf32
	@grub-file --is-x86-multiboot2 $(OBJ_DIR)/risx.elf32 \
		&& echo "MULTIBOOT2 OK" \
		|| echo "MULTIBOOT2 NONCOMPLIANT"

qemu: risx.iso
	@$(QEMU32) $(QEMUFLAGS)

qemu-debug: risx.iso
	@$(QEMU32) $(QEMUFLAGS) $(QEMUDEBUGFLAGS)
