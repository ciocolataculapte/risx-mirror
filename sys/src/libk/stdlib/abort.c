#include <stdnoreturn.h>
#include "stdio.h"
#include "stdlib.h"

noreturn void abort(void) {
	printf("kernel: panic: abort()\n");
    for(;;);
}
