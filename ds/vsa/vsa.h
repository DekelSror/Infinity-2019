/*==============================================================================
Variable Size Allocator
Header
OL66
Version 1.0
==============================================================================*/

#ifndef V_SIZE_ALLOCATOR
#define V_SIZE_ALLOCATOR

#include <stddef.h>        /* size_t */

typedef struct vsa_s vsa_t;

/*
Initialize a new allocator for a given buffer.

        Arguments:
                buffer - the buffer for the allocator
                buffer_size - size of the buffer

Returns a reference to the new allocator.
        For any buffer_size too small, returns NULL.

        Complexity O(1)
*/
vsa_t *VSAInit(void *buffer, size_t buffer_size);

/*
Allocate a new block.

        Arguments:
                allocator - the allocator to allocate with
                block_size - size of the block to be allocated

Returns a reference to the new block.


        Complexity O(n)
*/
void *VSAAlloc(vsa_t *allocator, size_t block_size);

/*
Free a given block.

        Arguments:
                block - the block to free.

If block-size is 0, returns NULL.

        Complexity O(1)
*/
void VSAFree(void *block);


/* for testing */
int VerifyBlock(void *block);

#endif /* V_SIZE_ALLOCATOR */
