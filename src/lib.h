#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#ifndef LIB
#define LIB

FILE * Fopen(const char *, const char *);
void * Malloc(size_t);
void * Realloc(void *, size_t);

#endif