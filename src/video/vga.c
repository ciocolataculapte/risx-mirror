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

// void vga_set_cursor_position(uint8_t col, uint8_t row) {
//     CURSOR_COL = col;
//     CURSOR_ROW = row;
// }

void scroll(size_t lines) {
    struct vga_char* vga_memory = VGA_MEM_ADDR;

    for (size_t row = 0; row < VGA_ROWS - lines; row = row + 1) {
        for (size_t col = 0; col < VGA_COLS; col = col + 1) {
            vga_memory[row * VGA_COLS + col] = vga_memory[(row + lines) * VGA_COLS + col];
        }
    }

    for (size_t row = VGA_ROWS - lines; row < VGA_ROWS; row = row + 1) {
        for (size_t col = 0; col < VGA_COLS; col = col + 1) {
            vga_memory[row * VGA_COLS + col].character = BLANK;
            vga_memory[row * VGA_COLS + col].attribute = BACKGROUND_COLOR | FOREGROUND_COLOR;
        }
    }

    if (CURSOR_ROW >= lines) {
        CURSOR_ROW = CURSOR_ROW - lines;
    } else {
        CURSOR_ROW = 0;
    }
}

void putc(char c) {
    struct vga_char* vga_memory = VGA_MEM_ADDR;

    if (CURSOR_ROW >= VGA_ROWS) {
        scroll(1);
        CURSOR_ROW = VGA_ROWS - 1;
    }

    if (c == NEWLINE) {
        CURSOR_COL = 0;
        CURSOR_ROW = CURSOR_ROW + 1;
    } else {
        vga_memory[CURSOR_ROW * VGA_COLS + CURSOR_COL].character = c;
        vga_memory[CURSOR_ROW * VGA_COLS + CURSOR_COL].attribute = BACKGROUND_COLOR | FOREGROUND_COLOR;

        CURSOR_COL = CURSOR_COL + 1;

        if (CURSOR_COL >= VGA_COLS) {
            CURSOR_COL = 0;
            CURSOR_ROW = CURSOR_ROW + 1;
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
