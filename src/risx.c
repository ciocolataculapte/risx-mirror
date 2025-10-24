#include <stdint.h>
#include <multiboot2.h>
#include <vga.h>

uint32_t risx(uint32_t magic, uint32_t addr) {
    vga_set_background_color(BG_BLUE);
    vga_set_foreground_color(FG_WHITE);

    clrscr();
    puts("Hello world!\n");

    return 0xDEADBEEF;
}
