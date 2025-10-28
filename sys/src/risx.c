#include <stdint.h>
#include <stdnoreturn.h>

#include "multiboot2.h"
#include "vga.h"

uint32_t validate_mbi(uint32_t magic, uintptr_t addr) {
    if (magic != MULTIBOOT2_BOOTLOADER_MAGIC) {
        vga_puts("error: invalid magic number\n");
        return 1;
    }

    if ((addr & 0x7) != 0) {
        vga_puts("error: unaligned multiboot2 info structure\n");
        return 1;
    }

    vga_puts("multiboot2 info structure is valid\n");

    #define ALIGN_UP(value, align) (((value) + (align) - 1) & ~((align) - 1))

    uintptr_t tag_addr = addr + 8;
    struct multiboot2_tag *tag = (struct multiboot2_tag *)tag_addr;

    while (tag->type != MULTIBOOT2_TAG_TYPE_END) {
        switch (tag->type) {
            case MULTIBOOT2_TAG_TYPE_CMDLINE:
                vga_puts("present: command line tag\n");
                break;

            case MULTIBOOT2_TAG_TYPE_BOOT_LOADER_NAME:
                vga_puts("present: boot loader name tag\n");
                break;

            case MULTIBOOT2_TAG_TYPE_MODULE:
                vga_puts("present: module tag\n");
                break;

            case MULTIBOOT2_TAG_TYPE_BASIC_MEMINFO:
                vga_puts("present: basic meminfo tag\n");
                break;

            case MULTIBOOT2_TAG_TYPE_BOOTDEV:
                vga_puts("present: bootdev tag\n");
                break;

            case MULTIBOOT2_TAG_TYPE_MMAP:
                vga_puts("present: mmap tag\n");
                break;

            case MULTIBOOT2_TAG_TYPE_FRAMEBUFFER:
                vga_puts("present: framebuffer tag\n");
                break;
        }

        tag_addr += ALIGN_UP(tag->size, 8);
        tag = (struct multiboot2_tag *)tag_addr;
    }

    #undef ALIGN_UP

    return 0;
}

noreturn void risx(uint32_t magic, uintptr_t addr) {
    vga_set_background_color(BG_BLACK);
    vga_set_foreground_color(FG_LIGHT_GREY);
    vga_clrscr();

    if (validate_mbi(magic, addr) != 0) {
        vga_puts("error: multiboot2 parsing failed. halted.");
        for (;;);
    }

    vga_puts("Hello world!\n");

    for (;;);
}

