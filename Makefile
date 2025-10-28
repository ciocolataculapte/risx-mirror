CC := i686-elf-gcc
CPPFLAGS := -Isys/include
CFLAGS := -std=c17 -ffreestanding -O2 -Wall -Wextra -g
LDFLAGS := -T sys/src/kernel.ld -ffreestanding -O2 -nostdlib -lgcc -g

OBJ_DIR := target

QEMU32 := qemu-system-i386
QEMUFLAGS := -m 4G -cdrom $(OBJ_DIR)/risx.iso
QEMUDEBUGFLAGS := -s -S -monitor stdio

.PHONY: all clean check qemu qemu-debug sys iso

all: sys iso

sys:
	# Ask the sys sub-make to write its outputs directly into the root-level OBJ_DIR
	$(MAKE) -C sys OBJ_DIR=$(CURDIR)/$(OBJ_DIR)

iso: $(OBJ_DIR)/risx.elf32
	@mkdir -p $(OBJ_DIR)/iso/boot/grub
	@cp config/grub/grub.cfg $(OBJ_DIR)/iso/boot/grub/grub.cfg
	@cp $(OBJ_DIR)/risx.elf32 $(OBJ_DIR)/iso/boot/risx.elf32
	@grub-mkrescue -o $(OBJ_DIR)/risx.iso $(OBJ_DIR)/iso \
		&& echo "ISO OK" \
		|| echo "ISO FAILED"

$(OBJ_DIR)/risx.elf32: sys
	# The sys sub-make builds the kernel directly into $(OBJ_DIR) (absolute path passed in),
	# so no copy is necessary here. This target exists to order the build and connect
	# downstream targets (iso, check, etc.).
	@test -f $(OBJ_DIR)/risx.elf32 || (echo "Expected $(OBJ_DIR)/risx.elf32 to be created by sys" && false)

clean:
	$(MAKE) -C sys clean
	@rm -rf $(OBJ_DIR)

check: $(OBJ_DIR)/risx.elf32
	@grub-file --is-x86-multiboot2 $(OBJ_DIR)/risx.elf32 \
		&& echo "MULTIBOOT2 OK" \
		|| echo "MULTIBOOT2 NONCOMPLIANT"

qemu: iso
	@$(QEMU32) $(QEMUFLAGS)

qemu-debug: iso
	@$(QEMU32) $(QEMUFLAGS) $(QEMUDEBUGFLAGS)
