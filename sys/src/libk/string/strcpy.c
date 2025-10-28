#include <stddef.h>
#include "string.h"

char* strcpy(char* restrict dest, const char* src) {
	char *dest_bytes = (char *)dest;
	char *src_bytes = (char *)src;
	while (*src_bytes) {
		*(dest_bytes++) = *(src_bytes++);
    }

	*dest_bytes = 0;

    return dest;
}
