#include "allocator.h"
#include <stdio.h>

static uint8_t heap[HEAP_SIZE];

// does not have to be thread safe
void heap_init(void)
{
    header *first = (header *)heap;
    first->size = sizeof(heap) - sizeof(header);
    first->free = true;
}

void *my_malloc(size_t n)
{
    header *curr = (header *)heap;
    size_t pos = 0;
    while (pos < HEAP_SIZE)
    {
        if (curr->free && curr->size >= n)
        {
            curr->free = false;
            return (uint8_t *)curr + sizeof(header);
        }
        size_t next_pos = pos + curr->size + sizeof(header);
        curr = (header *)(heap + next_pos);
        pos = next_pos;
    }
    return NULL;
}

void my_free(void *ptr)
{
    header *curr = (header *)((uint8_t *)ptr - sizeof(header));
    curr->free = true;
}

void heap_dump(void)
{
    header *curr = (header *)heap;
    size_t pos = 0;
    while (pos < HEAP_SIZE)
    {
        printf("Heap position: %d, Size: %d, free: %d \n", pos, curr->size, curr->free);
        size_t next_pos = pos + curr->size + sizeof(header);
        curr = (header *)(heap + next_pos);
        pos = next_pos;
    }
    return;
}
