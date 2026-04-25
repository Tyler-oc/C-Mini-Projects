#include "allocator.h"

int main()
{

    heap_init();

    void *a = my_malloc(10);
    void *b = my_malloc(20);
    void *c = my_malloc(5);
    heap_dump();

    my_free(b);
    heap_dump();

    void *d = my_malloc(15);
    heap_dump();
}