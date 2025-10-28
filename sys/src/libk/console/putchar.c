#include "console.h"
#include "vga.h"

int kputchar(int ic) {
	char c = (char) ic;
	vga_putc(c);

	return ic;
}
