/*==============================================================================
Data Structures - Circular Buffer
Header
Dekel Sror
Review - Ruben Gershon
RC 1
==============================================================================*/
#ifndef CIRCULAR_BUFFER
#define CIRCULAR_BUFFER

#include <stddef.h> /* size_t */
#include <unistd.h> /* ssize_t */

typedef struct cir_buf_t cir_buf_t;

/*
    args -
        capacity - desired size of cb in bytes
retuns a cir_buf_t pointer to a new cir_buf_t handle
*/
cir_buf_t *CirBufCreate(size_t capacity);

/*
    copies up to count bytes from buf to cb
    args -
        cb - cir_buf_t handle to write to,
        buf  - to read from,
        count bytes

    on success - returns number of bytes written
    on failure - returns -1
*/
ssize_t CirBufWrite(cir_buf_t *cb, const void *buf, size_t count);

/*
    copies up to count bytes from cb to buf
    args -
        cb to read from
        buf to write to
        count bytes
    on success - returns number of bytes read
    on failure - returns -1
*/
ssize_t CirBufRead(cir_buf_t *cb, void *buf, size_t count);

/*
    frees all memory used by cb
    args -
        cb - cir_buf_t handle
*/
void CirBufDestroy(cir_buf_t *cb);

/*
    returns total capacity of cb in bytes
    args -
        cb - cir_buf_t handle
*/
size_t CirBufCapacity(const cir_buf_t *cb);

/*
    returns number of bytes in cb available for writin
    args -
        cb - cir_buf_t handle
*/
size_t CirBufFreeSpace(const cir_buf_t *cb);
/*
    checks whether cb is empty
    args -
        cb - cir_buf_t handle
    returns 0 for false, otherwise != 0
*/
int CirBufIsEmpty(const cir_buf_t *cb);

#endif /*  CIRCULAR_BUFFER */
