#include <stdint.h>
#include <multiboot2.h>
#include <vga.h>

uint32_t risx(uint32_t magic, uint32_t addr);
uint32_t validate_mbi(uint32_t magic, uint32_t addr);

uint32_t risx(uint32_t magic, uint32_t addr) {
    vga_set_background_color(BG_BLUE);
    vga_set_foreground_color(FG_WHITE);
    clrscr();

    if (validate_mbi(magic, addr) != 0) {
        return 1;
    }

    puts("Hello world!\n");

    return 0;
}

uint32_t validate_mbi(uint32_t magic, uint32_t addr) {
    if (magic != MULTIBOOT2_BOOTLOADER_MAGIC) {
        puts("error: invalid magic number\n");
        return 1;
    }

    if ((addr & 0x7) != 0) {
        puts("error: unaligned multiboot2 info structure\n");
        return 1;
    }

    puts("multiboot2 info structure is valid\n");
    return 0;
}
