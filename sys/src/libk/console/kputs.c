#include "console.h"
#include "vga.h"

int kputs(const char* string) {
	return kprintf(string); // not efficient, but works for now
}
