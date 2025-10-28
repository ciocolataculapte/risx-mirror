#include <stdbool.h>
#include <stdint.h>
#include <stdnoreturn.h>
#include "console.h"
#include "multiboot2.h"
#include "stdlib.h"
#include "vga.h"

uint32_t validate_mbi(uint32_t magic, uintptr_t addr) {
    if (magic != MULTIBOOT2_BOOTLOADER_MAGIC) {
        kputs("error: invalid magic number\n");
        return 1;
    }

    if ((addr & 0x7) != 0) {
        kputs("error: unaligned multiboot2 info structure\n");
        return 1;
    }

    kputs("multiboot2 info structure is valid\n");

    #define ALIGN_UP(value, align) (((value) + (align) - 1) & ~((align) - 1))

    uintptr_t tag_addr = addr + 8;
    struct multiboot2_tag *tag = (struct multiboot2_tag *)tag_addr;

    while (tag->type != MULTIBOOT2_TAG_TYPE_END) {
        switch (tag->type) {
            case MULTIBOOT2_TAG_TYPE_CMDLINE:
                kputs("present: command line tag\n");
                break;

            case MULTIBOOT2_TAG_TYPE_BOOT_LOADER_NAME:
                kputs("present: boot loader name tag\n");
                break;

            case MULTIBOOT2_TAG_TYPE_MODULE:
                kputs("present: module tag\n");
                break;

            case MULTIBOOT2_TAG_TYPE_BASIC_MEMINFO:
                kputs("present: basic meminfo tag\n");
                break;

            case MULTIBOOT2_TAG_TYPE_BOOTDEV:
                kputs("present: bootdev tag\n");
                break;

            case MULTIBOOT2_TAG_TYPE_MMAP:
                kputs("present: mmap tag\n");
                break;

            case MULTIBOOT2_TAG_TYPE_FRAMEBUFFER:
                kputs("present: framebuffer tag\n");
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
        kputs("error: multiboot2 parsing failed. halted.");
        abort();
    }

    kprintf("Hello world from kprintf!\n");
    kdebugf("Hello world from kdebugf!\n");
    kerrorf("Hello world from kerrorf!\n");

    int i = -300;
    unsigned int j = 16;
    char c = 'A';
    void* p = (void*)0xDEADBEEF;
    static char* str = "This is a test string.";

    kprintf("int: %d\n", i);
    kprintf("unsigned int: %u\n", j);
    kprintf("char: %c\n", c);
    kprintf("hex: 0x%x\n", j);
    kprintf("pointer: 0x%p\n", p);
    kprintf("string: %s\n", str);

    abort();

    while (true);
}

