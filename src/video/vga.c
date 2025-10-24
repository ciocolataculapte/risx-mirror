#include <stddef.h>

#include "vga.h"

static uint8_t BACKGROUND_COLOR = BG_BLACK;
static uint8_t FOREGROUND_COLOR = FG_WHITE;

static uint8_t CURSOR_COL = 0;
static uint8_t CURSOR_ROW = 0;

void vga_set_background_color(uint8_t color) {
    BACKGROUND_COLOR = color;
}

void vga_set_foreground_color(uint8_t color) {
    FOREGROUND_COLOR = color;
}

void vga_set_cursor_position(uint8_t col, uint8_t row) {
    CURSOR_COL = col;
    CURSOR_ROW = row;
}

void putc(char c) {
        struct vga_char* vga_memory = VGA_MEM_ADDR;

        if (c == NEWLINE) {
                CURSOR_COL = 0;
                CURSOR_ROW = CURSOR_ROW + 1;
                if (CURSOR_ROW >= VGA_ROWS) {
                        CURSOR_ROW = 0;
                }
                return;
        }

        vga_memory[CURSOR_ROW * VGA_COLS + CURSOR_COL].character = c;
        vga_memory[CURSOR_ROW * VGA_COLS + CURSOR_COL].attribute = BACKGROUND_COLOR | FOREGROUND_COLOR;

        CURSOR_COL = CURSOR_COL + 1;

        if (CURSOR_COL >= VGA_COLS) {
                CURSOR_COL = 0;
                CURSOR_ROW = CURSOR_ROW + 1;
                if (CURSOR_ROW >= VGA_ROWS) {
                        CURSOR_ROW = 0;
                }
        }
}

void puts(const char* str) {
        while (*str != NULLCHAR) {
                putc(*str);
                str = str + 1;
        }
}

void clrscr() {
        struct vga_char* vga_memory = VGA_MEM_ADDR;

        for (size_t i = 0; i < VGA_COLS * VGA_ROWS; i = i + 1) {
                vga_memory[i].character = BLANK;
                vga_memory[i].attribute = BACKGROUND_COLOR | FOREGROUND_COLOR;
        }

        CURSOR_COL = 0;
        CURSOR_ROW = 0;
}
