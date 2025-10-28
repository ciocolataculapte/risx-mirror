#include "console.h"
#include "vga.h"

int kputs(const char* string) {
	return kprintf("%s\n", string);
}
