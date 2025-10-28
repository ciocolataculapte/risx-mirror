CC := i686-elf-gcc
CPPFLAGS := -Iinclude
CFLAGS := -std=c17 -ffreestanding -O2 -Wall -Wextra -Werror -g
LDFLAGS := -T src/kernel.ld -nostdlib -lgcc

SRCS := $(shell find src -name '*.S' -o -name '*.c')
OBJS := $(patsubst src/%.S,$(OBJ_DIR)/%.o,$(filter %.S,$(SRCS))) \
	$(patsubst src/%.c,$(OBJ_DIR)/%.o,$(filter %.c,$(SRCS)))
OBJ_DIR ?= target

all: $(OBJ_DIR)/risx.elf32

$(OBJ_DIR)/risx.elf32: $(OBJS) src/kernel.ld
	@mkdir -p $(OBJ_DIR)
	$(CC) $(OBJS) $(LDFLAGS) -o $(OBJ_DIR)/risx.elf32

$(OBJ_DIR)/%.o: src/%.S
	@mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

.PHONY: all
