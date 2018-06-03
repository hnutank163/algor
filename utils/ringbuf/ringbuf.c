#include "ringbuf.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define MIN(a, b) (a) < (b) ? (a) : (b)
struct ringbuf_st
{
    size_t capacity;
    char *  head;
    char *  tail;
    char *  write_ptr;
    char *  read_ptr;
    char *  buf;
};

ringbuf * ringbuf_new(size_t size)
{
    ringbuf *rb = (ringbuf *)malloc(sizeof(ringbuf));

    if (rb == NULL)
        return NULL;

    rb->capacity = size + 1; //avoid readptr == writeptr
    rb->buf = (char *) malloc(rb->capacity);
    if (rb->buf == NULL)
    {
        free(rb);
        return NULL;
    }

    rb->head = rb->write_ptr = rb->read_ptr = rb->buf;
    rb->tail = rb->head + rb->capacity;

    return rb;
}

void ringbuf_free(ringbuf *rb)
{
    if (rb)
    {
        if (rb->buf)
            free(rb->buf);
        free(rb);
    }
}

size_t ringbuf_put(ringbuf *rb, void *data, size_t size)
{
    assert(rb && data);

    const char *rptr = rb->read_ptr; //avoid another thread is read
    if (rptr <= rb->write_ptr)
    {
        //################### 
        //h   r  w          t
        if (size > rb->capacity - (rb->write_ptr - rptr) - 1)
        {
            size = rb->capacity - (rb->write_ptr - rptr) - 1;
        }

        size_t back_size = MIN(size, rb->tail - rb->write_ptr);
        size_t front_size = size - back_size;
        if (front_size)
        {
            memcpy(rb->write_ptr, data, back_size);
            memcpy(rb->head, (char *)data+back_size, front_size);
            rb->write_ptr = rb->head +front_size;
        }
        else
        {
            memcpy(rb->write_ptr, data, back_size);
            rb->write_ptr += back_size;
        }
    }
    else
    {
        
        //###################
        // h   w    r        t
        if (size > (size_t)(rptr - rb->write_ptr-1))
        {
            size = rptr - rb->write_ptr - 1;
        }
        memcpy(rb->write_ptr, data, size);
        rb->write_ptr += size;
    }

    return size;
}

size_t ringbuf_get(ringbuf *rb, void *data, size_t size)
{
    const char *wptr = rb->write_ptr; //avoid another thread is write

    if (wptr >= rb->read_ptr)
    {
        // #################
        // h   r  w        t
        if (size > (size_t)(wptr - rb->read_ptr))
            size = wptr - rb->read_ptr;
        memcpy(data, rb->read_ptr, size);
        rb->read_ptr += size;
    }
    else
    {
        // ################
        // h   w  r       t
        if (size > rb->capacity - (rb->read_ptr - wptr))
            size = rb->capacity - (rb->read_ptr - wptr);

        size_t back_size = MIN(size, rb->tail - rb->read_ptr);
        size_t front_size = size - back_size;
        if (front_size)
        {
            memcpy(data, rb->read_ptr, back_size);
            memcpy((char *)data + back_size, rb->head, front_size);
            rb->read_ptr = rb->head + front_size;
        }
        else
        {
            memcpy(data, rb->read_ptr, size);
            rb->read_ptr += size;
        }
    }

    return size;
}
