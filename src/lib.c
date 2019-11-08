#include "lib.h"

FILE * Fopen(const char * filename, const char * permissions){
    FILE * file = fopen(filename, permissions);
    if(!file)
        exit(1);

    return file;
}

void * Malloc(size_t size){
    void * allocated = malloc(size);
    if(!allocated)
        exit(1);
    
    return allocated;
}

void * Realloc(void * ptr, size_t size){
    void * allocated = realloc(ptr, size);
    if(!allocated)
        exit(1);
    
    return allocated;
}