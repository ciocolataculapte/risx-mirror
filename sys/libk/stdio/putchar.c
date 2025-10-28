#include "stdio.h"
#include "vga.h"

int putchar(int ic) {
	char c = (char) ic;
	vga_putc(c);

	return ic;
}
