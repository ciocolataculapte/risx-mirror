OBJ_DIR := target

QEMU32 := qemu-system-i386
QEMUFLAGS := -m 4G -cdrom $(OBJ_DIR)/risx.iso
QEMUDEBUGFLAGS := -s -S -monitor stdio

.PHONY: all clean check qemu qemu-debug sys iso

all: sys iso

sys:
	$(MAKE) -C sys OBJ_DIR=$(CURDIR)/$(OBJ_DIR)

iso: sys
	@mkdir -p $(OBJ_DIR)/iso/boot/grub
	@cp config/grub/grub.cfg $(OBJ_DIR)/iso/boot/grub/grub.cfg
	@cp $(OBJ_DIR)/risx.elf32 $(OBJ_DIR)/iso/boot/risx.elf32
	@grub-mkrescue -o $(OBJ_DIR)/risx.iso $(OBJ_DIR)/iso \
		&& echo "ISO OK" \
		|| echo "ISO FAILED"

clean:
	@rm -rf $(OBJ_DIR)

check: $(OBJ_DIR)/risx.elf32
	@grub-file --is-x86-multiboot2 $(OBJ_DIR)/risx.elf32 \
		&& echo "MULTIBOOT2 OK" \
		|| echo "MULTIBOOT2 NONCOMPLIANT"

qemu: iso
	@$(QEMU32) $(QEMUFLAGS)

qemu-debug: iso
	@$(QEMU32) $(QEMUFLAGS) $(QEMUDEBUGFLAGS)
