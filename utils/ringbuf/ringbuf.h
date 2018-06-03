#ifndef _RING_BUF_H_
#define _RING_BUF_H_ value

#include <stdlib.h>
#include <string.h>

struct ringbuf_st;
typedef struct ringbuf_st ringbuf;

ringbuf * ringbuf_new(unsigned int size);
void ringbuf_free(ringbuf *rb);
unsigned int ringbuf_put(ringbuf *rb, const void *data, unsigned int size);
unsigned int ringbuf_get(ringbuf *rb, void *data, unsigned int size);

#endif /* ifndef _RING_BUF_H_ */
