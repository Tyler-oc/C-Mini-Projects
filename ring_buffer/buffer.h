#pragma once
#include <stdint.h>
#include <stdbool.h>
#define RING_CAPACITY 8;

typedef struct
{
    uint32_t data[RING_CAPACITY];
    uint32_t head;
    uint32_t tail;
} rb_buf_t;

void ring_init(rb_buf_t *rb);

bool ring_push(rb_buf_t *rb, uint32_t n);

uint32_t ring_pop(rb_buf_t *rb);