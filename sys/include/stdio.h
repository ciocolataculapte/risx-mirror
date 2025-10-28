#ifndef STDIO_H
#define STDIO_H 1

#define EOF (-1)

int printf(const char* restrict format, ...);
int putchar(int c);
int puts(const char* s);

#endif
