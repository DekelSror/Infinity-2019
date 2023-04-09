/*==============================================================================
Data Structures - Circular Buffer
Module
Dekel Sror
Review - Ruben Gershon
RC 1
==============================================================================*/
#include <stdlib.h> /* malloc, free, NULL */
#include <assert.h> /* assert             */
#include <string.h> /* memcpy             */
#include <errno.h>  /* errno              */

#include "circbuff.h"

#define MIN2(a, b) (((a) < (b)) ? (a) : (b))

struct cir_buf_t
{
    size_t capacity;
    char *write_pos;
    char *read_pos;
    char buffer[1];
};

cir_buf_t *CirBufCreate(size_t capacity)
{
    cir_buf_t *new_cb = (cir_buf_t*)malloc(sizeof(cir_buf_t) + capacity + 1);

    if (NULL == new_cb)
    {
        errno = ENOMEM;
        return NULL;
    }

    new_cb->capacity = capacity;

/* nothing to read, buffer is clear */
    new_cb->write_pos = new_cb->buffer;
    new_cb->read_pos  = new_cb->buffer;

    return new_cb;
}

void CirBufDestroy(cir_buf_t *cb)
{
    assert(cb);
    free(cb);
    cb = NULL;
}

ssize_t CirBufWrite(cir_buf_t *cb, const void *buf, size_t count)
{
    ssize_t total_w_bytes = 0;
    char *c_buf = (char *)buf;
    size_t till_end = 0;
    int phase_bytes = 0;

    assert(cb);
    assert(buf);

    if(!cb || !buf)
    {
        errno = EINVAL;
        return -1;
    }

    total_w_bytes = MIN2(CirBufFreeSpace(cb), count);
    till_end = cb->capacity - (cb->write_pos - cb->buffer) + 1;
    phase_bytes = MIN2((size_t)total_w_bytes, till_end);

/* phase 1 - copy till end of buffer */
    memcpy(cb->write_pos, c_buf, phase_bytes);
    cb->write_pos += phase_bytes;
    c_buf += phase_bytes;
    phase_bytes = total_w_bytes - phase_bytes;

/* phase 2 - copy from start to read_pos or count */
    if (phase_bytes)
    {
        cb->write_pos = cb->buffer;
        memcpy(cb->write_pos, c_buf, phase_bytes);
        cb->write_pos += phase_bytes;
    }

    return total_w_bytes;
}

ssize_t CirBufRead(cir_buf_t *cb, void *buf, size_t count)
{
    size_t total_r_bytes = 0;
    char *c_buf = (char *)buf;
    size_t till_end = 0;
    int phase_bytes = 0;

    assert(cb);
    assert(buf);

    if(!cb || !buf)
    {
        errno = EINVAL;
        return -1;
    }

    total_r_bytes = MIN2((cb->capacity - CirBufFreeSpace(cb)), count);
    till_end = cb->buffer + cb->capacity + 1 - cb->read_pos;
    phase_bytes = MIN2((size_t)total_r_bytes, till_end);

/* phase 1 - copy till end of buffer */
    memcpy(c_buf, cb->read_pos, phase_bytes);
    cb->read_pos += phase_bytes;
    c_buf += phase_bytes;
    phase_bytes = total_r_bytes - phase_bytes;

/* phase 2 - copy from start to read_pos or count */
    if (phase_bytes)
    {
        cb->read_pos = cb->buffer;
        memcpy(c_buf, cb->read_pos, phase_bytes);
        cb->read_pos +=  phase_bytes;
    }

    return total_r_bytes;
}

size_t CirBufCapacity(const cir_buf_t *cb)
{
    assert(cb);

    return cb->capacity;
}

/* get delta. return write_space */
size_t CirBufFreeSpace(const cir_buf_t *cb)
{
    int delta = 0;

    assert(cb);

    delta = cb->write_pos - cb->read_pos;
    return (delta >= 0) ? ((long)cb->capacity - delta) : -(delta + 1);
}

/* empty means is fully read. write_space == capacity */
int CirBufIsEmpty(const cir_buf_t *cb)
{
    assert(cb);

    return cb->write_pos == cb->read_pos;
}
