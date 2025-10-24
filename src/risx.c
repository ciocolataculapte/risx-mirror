#include <stdint.h>
#include "multiboot2.h"
#include "vga.h"

uint32_t risx(uint32_t magic, uintptr_t addr);
uint32_t validate_mbi(uint32_t magic, uintptr_t addr);

uint32_t risx(uint32_t magic, uintptr_t addr) {
    vga_set_background_color(BG_LIGHT_BLUE);
    vga_set_foreground_color(FG_WHITE);
    clrscr();

    if (validate_mbi(magic, addr) != 0) {
        return 1;
    }

    puts("Hello world!\n");

    return 0;
}

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
                puts("processed command line tag\n");
                break;

            case MULTIBOOT2_TAG_TYPE_BOOT_LOADER_NAME:
                puts("processed boot loader name tag\n");
                break;

            case MULTIBOOT2_TAG_TYPE_MODULE:
                puts("processed module tag\n");
                break;

            case MULTIBOOT2_TAG_TYPE_BASIC_MEMINFO:
                puts("processed basic meminfo tag\n");
                break;

            case MULTIBOOT2_TAG_TYPE_BOOTDEV:
                puts("processed bootdev tag\n");
                break;

            case MULTIBOOT2_TAG_TYPE_MMAP:
                puts("processed mmap tag\n");
                break;

            case MULTIBOOT2_TAG_TYPE_FRAMEBUFFER:
                puts("processed framebuffer tag\n");
                break;
        }

        tag_addr += ALIGN_UP(tag->size, 8);
        tag = (struct multiboot2_tag *)tag_addr;
    }

    #undef ALIGN_UP

    return 0;
}
