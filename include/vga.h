#ifndef VGA_H
#define VGA_H

#include <stdint.h>

struct vga_char {
    uint8_t character;
    uint8_t attribute;
};

#define VGA_COLS                ((uint8_t)80)
#define VGA_ROWS                ((uint8_t)25)
#define VGA_MEM_ADDR            ((struct vga_char*)0xB8000)

#define FG_BLACK                ((uint8_t)0)
#define FG_BLUE                 ((uint8_t)1)
#define FG_GREEN                ((uint8_t)2)
#define FG_CYAN                 ((uint8_t)3)
#define FG_RED                  ((uint8_t)4)
#define FG_MAGENTA              ((uint8_t)5)
#define FG_BROWN                ((uint8_t)6)
#define FG_LIGHT_GREY           ((uint8_t)7)
#define FG_DARK_GREY            ((uint8_t)8)
#define FG_LIGHT_BLUE           ((uint8_t)9)
#define FG_LIGHT_GREEN          ((uint8_t)10)
#define FG_LIGHT_CYAN           ((uint8_t)11)
#define FG_LIGHT_RED            ((uint8_t)12)
#define FG_LIGHT_MAGENTA        ((uint8_t)13)
#define FG_LIGHT_BROWN          ((uint8_t)14)
#define FG_WHITE                ((uint8_t)15)

#define BG_BLACK                ((uint8_t)0 << 4)
#define BG_BLUE                 ((uint8_t)1 << 4)
#define BG_GREEN                ((uint8_t)2 << 4)
#define BG_CYAN                 ((uint8_t)3 << 4)
#define BG_RED                  ((uint8_t)4 << 4)
#define BG_MAGENTA              ((uint8_t)5 << 4)
#define BG_BROWN                ((uint8_t)6 << 4)
#define BG_LIGHT_GREY           ((uint8_t)7 << 4)
#define BG_DARK_GREY            ((uint8_t)8 << 4)
#define BG_LIGHT_BLUE           ((uint8_t)9 << 4)
#define BG_LIGHT_GREEN          ((uint8_t)10 << 4)
#define BG_LIGHT_CYAN           ((uint8_t)11 << 4)
#define BG_LIGHT_RED            ((uint8_t)12 << 4)
#define BG_LIGHT_MAGENTA        ((uint8_t)13 << 4)
#define BG_LIGHT_BROWN          ((uint8_t)14 << 4)
#define BG_WHITE                ((uint8_t)15 << 4)

#define BACKSPACE               ((char)'\b')
#define BLANK                   ((char)' ')
#define CARRIAGE_RETURN         ((char)'\r')
#define NEWLINE                 ((char)'\n')
#define NULLCHAR                ((char)'\0')
#define TAB                     ((char)'\t')

// video/vga.c
void vga_set_background_color(uint8_t color);
void vga_set_foreground_color(uint8_t color);
void vga_set_cursor_position(uint8_t col, uint8_t row);
void clrscr();
void putc(char c);
void puts(const char* str);

#endif
