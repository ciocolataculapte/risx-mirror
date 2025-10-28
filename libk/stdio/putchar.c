#include <stdio.h>

#if defined(__is_libk)
#include <console.h>
#endif

int putchar(int ic) {
#if defined(__is_libk)
	char c = (char) ic;
	putc(c);
#else
	// TODO: Implement stdio and the write system call.
#endif
	return ic;
}
