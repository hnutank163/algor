#ifndef _RING_BUF_H_
#define _RING_BUF_H_ value

#include <stdlib.h>
#include <string.h>

struct ringbuf_st;
typedef struct ringbuf_st ringbuf;

ringbuf * ringbuf_new(size_t size);
void ringbuf_free(ringbuf *rb);
size_t ringbuf_put(ringbuf *rb, void *data, size_t size);
size_t ringbuf_get(ringbuf *rb, void *data, size_t size);

#endif /* ifndef _RING_BUF_H_ */
