#include "stdio.h"
#include "vga.h"

int puts(const char* string) {
	return printf("%s\n", string);
}
