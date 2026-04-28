#include "allocator.h"

int main()
{

    heap_init();

    void *a = my_malloc(10);
    void *b = my_malloc(20);
    void *c = my_malloc(5);
    heap_dump();
    printf("Got to first dump");
    my_free(c);
    my_free(b);
    heap_dump();
    printf("Got to free");

    void *d = my_malloc(15);
    heap_dump();
    return 0;
}