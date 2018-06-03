#include "ringbuf.h"
#include <stdlib.h>
#include <string.h>

#define MIN(a, b) (a) < (b) ? (a) : (b)
#define POW_OF_TWO(x) (((x) & (x-1)) == 0)

struct ringbuf_st
{
    unsigned char *buf;          //buffer alloca from heap
    unsigned int size;  //total size of buf
    unsigned int in;    //data put offset (in%size)
    unsigned int out;   //data get offset (out%size)
};

ringbuf * ringbuf_new(unsigned int size)
{
    if (!POW_OF_TWO(size))
    {
        return NULL;
    }

    ringbuf *rb = (ringbuf *)malloc(sizeof(ringbuf));
    if (rb == NULL)
        return NULL;

    rb->size = size;
    rb->buf = (unsigned char *)malloc(rb->size);
    if (rb->buf == NULL)
    {
        free(rb);
        return NULL;
    }

    rb->in = rb->out = 0;
}

unsigned int ringbuf_put(ringbuf *rb, const void *data, unsigned int len)
{
    unsigned int l;
    len = MIN(len, rb->size - rb->in + rb->out);

    //put data from rb->in to rb->buf end
    l = MIN(len, rb->size - (rb->in & (rb->size-1)));
    memcpy(rb->buf + (rb->in & (rb->size-1)), data, l);

    //put rest data from begining of rb->buf
    memcpy(rb->buf, (unsigned char *)data + l, len - l);
    rb->in += len;

    return len;
}

unsigned int ringbuf_get(ringbuf *rb, void *data, unsigned int len)
{
    unsigned int l;
    len = MIN(len, rb->in - rb->out);
    //get data from rb->out to rb->buf end
    l = MIN(len, rb->size - (rb->out & (rb->size - 1)));
    memcpy(data, rb->buf + (rb->out & (rb->size - 1)), l);

    //get rest data from begining of rb->buf
    memcpy((unsigned char *)data + l, rb->buf, len - l);
    rb->out += len;

    return len;
}
