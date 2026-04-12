#include "buffer.h"

void ring_init(rb_buf_t *rb)
{
    atomic_store_explicit(&rb->head, 0, memory_order_relaxed);
    atomic_store_explicit(&rb->tail, 0, memory_order_relaxed);
}

bool ring_push(rb_buf_t *rb, uint32_t n)
{
    uint32_t head = atomic_load_explicit(&rb->head, memory_order_acquire);
    uint32_t tail = atomic_load_explicit(&rb->tail, memory_order_acquire);
    // does moving the head forward land on the tail
    if (((head + 1) % RING_CAPACITY) == tail)
    {
        return false;
    }
    // write then advance
    rb->data[head] = n;
    atomic_store_explicit(&rb->head, (head + 1) % RING_CAPACITY, memory_order_release);
    return true;
}

bool ring_pop(rb_buf_t *rb, uint32_t *out)
{
    uint32_t head = atomic_load_explicit(&rb->head, memory_order_acquire);
    uint32_t tail = atomic_load_explicit(&rb->tail, memory_order_acquire);
    if (head == tail)
    {
        return false;
    }
    *out = rb->data[tail];
    atomic_store_explicit(&rb->tail, (tail + 1) % RING_CAPACITY, memory_order_release);
    return true;
}