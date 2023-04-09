/*==============================================================================
Variable Size Allocator
Module
Dekel Sror
Review: Tal Shabtai
OL66
Version 2
==============================================================================*/
#include <assert.h>

#include "vsa.h"

/* public user handle */
struct vsa_s
{
    size_t total_bytes;
};

/* private block metadata type */
typedef struct blk_meta_s
{
    long size_flag;

#ifndef DNDEBUG
    size_t magic_num;
#endif /* DNDEBUG */

}blk_meta_t;

static int Defrag(blk_meta_t *dest, blk_meta_t *src);
static void TryFragment(blk_meta_t *blk, size_t block_size);
static void WriteBlockMeta(blk_meta_t *block, long block_size);

#define WORD_SIZE (sizeof(void *))

/* for debugging */
#define _MAGIC_ (0xdeadbeeflu)

#define ABS(x) ((x < 0) ? (-x) : (x))
#define BLOCK_SIZE_ALIGN(blk) (sizeof(blk_meta_t) + \
               ((0 == (blk % WORD_SIZE)) ? 0 : (WORD_SIZE - (blk % WORD_SIZE))))

#define IN_VSA_BOUNDS(vsa, blk) ((char *)blk < ((char *)vsa + vsa->total_bytes))
#define FIRST_BLOCK(vsa) ((blk_meta_t *)((char *)vsa + sizeof(vsa_t)))
#define NEXT_BLOCK(blk) ((blk_meta_t *)((char *)blk + ABS(blk->size_flag)))

#define BLOCK_META(blk) ((blk_meta_t *)((char *)blk - sizeof(blk_meta_t)))
#define USER_BLOCK_START(blk) ((char *)blk + sizeof(blk_meta_t))

#define SET_FLAG(blk)       (blk->size_flag = -blk->size_flag)
#define ALLOCATE_BLOCK(blk) (SET_FLAG(blk))
#define FREE_BLOCK(blk)     (SET_FLAG(blk))

void *VSAAlloc(vsa_t *allocator, size_t block_size)
{
    blk_meta_t *block = FIRST_BLOCK(allocator);

    assert(allocator);

    block_size += BLOCK_SIZE_ALIGN(block_size);

    while (block->size_flag < (long)block_size)
    {
        blk_meta_t *next_block = NEXT_BLOCK(block);

        assert(block->magic_num == _MAGIC_);

        if (!IN_VSA_BOUNDS(allocator, next_block))
        {
            return NULL;
        }
        else if (Defrag(block, next_block))
        {
            continue;
        }

        block = NEXT_BLOCK(block);
    }

    TryFragment(block, block_size);

    ALLOCATE_BLOCK(block);

    return USER_BLOCK_START(block);
}

vsa_t *VSAInit(void *buffer, size_t buffer_size)
{
    vsa_t *new_vsa = buffer;
    blk_meta_t *first_block = NULL;

    assert(buffer);

    /* no use for remainder as blocks are aligned */
    new_vsa->total_bytes = buffer_size - (buffer_size % WORD_SIZE);
    first_block = FIRST_BLOCK(buffer);
    WriteBlockMeta(first_block, new_vsa->total_bytes - sizeof(vsa_t));

    return new_vsa;
}

void VSAFree(void *block)
{
    blk_meta_t *to_free = BLOCK_META(block);

    assert(to_free->magic_num == _MAGIC_);

    FREE_BLOCK(to_free);
}

/* sets meta for next free block if possible */
static void TryFragment(blk_meta_t *block, size_t block_size)
{
    long frag_block_size = block->size_flag - block_size;

    if (frag_block_size >= (long)sizeof(blk_meta_t))
    {
        blk_meta_t *new_meta = NULL;

        block->size_flag = (long)block_size;
        new_meta = NEXT_BLOCK(block);
        WriteBlockMeta(new_meta, frag_block_size);
    }
}

/* unites two adjacent blocks if possible */
static int Defrag(blk_meta_t *dest, blk_meta_t *src)
{
    if ((0 > dest->size_flag) || (0 > src->size_flag))
    {
        return 0;
    }

    dest->size_flag += src->size_flag;

    return 1;
}

static void WriteBlockMeta(blk_meta_t *block, long block_size)
{
    block->size_flag = block_size;

    #ifndef DNDEBUG
    block->magic_num = _MAGIC_;
    #endif /* DNDEBUG */
}
