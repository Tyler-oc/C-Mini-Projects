#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdatomic.h>
#define HEAP_SIZE 256

typedef struct
{
    uint32_t size;
    bool free;
} header;

void heap_init();

void *my_malloc(size_t n);

void my_free(void *ptr);

void heap_dump();