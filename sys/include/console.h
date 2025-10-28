#ifndef STDIO_H
#define STDIO_H 1

#define EOF (-1)

int kprintf(const char* restrict format, ...);
int kdebugf(const char* restrict format, ...);
int kputchar(int c);
int kputs(const char* s);

#endif
