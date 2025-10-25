#include <stdint.h>
#include <stdnoreturn.h>

#include "multiboot2.h"
#include "vga.h"

uint32_t validate_mbi(uint32_t magic, uintptr_t addr) {
    if (magic != MULTIBOOT2_BOOTLOADER_MAGIC) {
        puts("error: invalid magic number\n");
        return 1;
    }

    if ((addr & 0x7) != 0) {
        puts("error: unaligned multiboot2 info structure\n");
        return 1;
    }

    puts("multiboot2 info structure is valid\n");

    #define ALIGN_UP(value, align) (((value) + (align) - 1) & ~((align) - 1))

    uintptr_t tag_addr = addr + 8;
    struct multiboot2_tag *tag = (struct multiboot2_tag *)tag_addr;

    while (tag->type != MULTIBOOT2_TAG_TYPE_END) {
        switch (tag->type) {
            case MULTIBOOT2_TAG_TYPE_CMDLINE:
                puts("present: command line tag\n");
                break;

            case MULTIBOOT2_TAG_TYPE_BOOT_LOADER_NAME:
                puts("present: boot loader name tag\n");
                break;

            case MULTIBOOT2_TAG_TYPE_MODULE:
                puts("present: module tag\n");
                break;

            case MULTIBOOT2_TAG_TYPE_BASIC_MEMINFO:
                puts("present: basic meminfo tag\n");
                break;

            case MULTIBOOT2_TAG_TYPE_BOOTDEV:
                puts("present: bootdev tag\n");
                break;

            case MULTIBOOT2_TAG_TYPE_MMAP:
                puts("present: mmap tag\n");
                break;

            case MULTIBOOT2_TAG_TYPE_FRAMEBUFFER:
                puts("present: framebuffer tag\n");
                break;
        }

        tag_addr += ALIGN_UP(tag->size, 8);
        tag = (struct multiboot2_tag *)tag_addr;
    }

    #undef ALIGN_UP

    return 0;
}

noreturn void risx(uint32_t magic, uintptr_t addr) {
    vga_set_background_color(BG_LIGHT_BLUE);
    vga_set_foreground_color(FG_WHITE);
    clrscr();

    if (validate_mbi(magic, addr) != 0) {
        puts("error: multiboot2 parsing failed. halted.");
        for (;;);
    }

    puts("Hello world!\n");

    for (;;);
}

