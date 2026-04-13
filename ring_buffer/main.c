#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sched.h>
#include "buffer.h"

void *writer(void *arg)
{
    rb_buf_t *rb = (rb_buf_t *)arg;
    for (int i = 0; i < 49; i++)
    {
        while (!ring_push(rb, i))
            sched_yield();
    }
    return NULL;
}

void *reader(void *arg)
{
    rb_buf_t *rb = (rb_buf_t *)arg;
    uint32_t val;
    bool pass = true;
    for (int i = 0; i < 49; i++)
    {
        while (!ring_pop(rb, &val))
            sched_yield();

        if (val != i)
        {
            pass = false;
        }
    }
    printf("%s", pass ? "PASS" : "FAIL");
    return NULL;
}

int main()
{
    rb_buf_t *rb = malloc(sizeof(rb_buf_t));
    uint32_t val;
    pthread_t producer;
    pthread_t consumer;
    if (rb == NULL)
    {
        return 1;
    }
    ring_init(rb);

    pthread_create(&producer, NULL, writer, rb);
    pthread_create(&consumer, NULL, reader, rb);

    pthread_join(producer, NULL);
    pthread_join(consumer, NULL);

    free(rb);
    return 0;
}