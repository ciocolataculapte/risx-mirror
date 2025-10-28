#ifndef _STRING_H
#define _STRING_H 1

#include <stddef.h>

// compiler needs these built-in functions
void* memcpy(void* restrict s1, const void* restrict s2, size_t n);
void* memmove(void* s1, const void* s2, size_t n);
int memcmp(const void* s1, const void* s2, size_t n);
void* memset(void* s, int c, size_t n);

char* strcpy(char* restrict s1, const char* restrict s2);
char* strcat(char* restrict s1, const char* restrict s2);
int strcmp(const char* s1, const char* s2);
size_t strlen(const char* s);

#endif
