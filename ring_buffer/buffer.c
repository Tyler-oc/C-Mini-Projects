#include "buffer.h"

void ring_init(rb_buf_t *rb)
{
    rb->head = 0;
    rb->tail = 0;
}

bool ring_push(rb_buf_t *rb, uint32_t n)
{
    if (rb->head == rb->tail - 1)
    {
        return false;
    }
    rb->head = rb->head + 1 % RING_CAPACITY;
    rb->data[rb->head] = n;
    return true;
}

uint32_t ring_pop(rb_buf_t *rb)
{
    if (rb->head == rb->tail)
    {
        return 0;
    }
    uint32_t result = rb->data[rb->tail];
    rb->tail = rb->tail + 1 % RING_CAPACITY;
    return result;
}