#include <stdbool.h>
#include <stdnoreturn.h>
#include "console.h"
#include "stdlib.h"

noreturn void abort(void) {
	kprintf("kernel: panic: abort()\n");
    while (true);
}
