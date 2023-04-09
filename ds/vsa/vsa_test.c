/*==============================================================================
Variable Size Allocator
Tests
Dekel Sror
Review: Tal Shabtai
OL66
Version 1
==============================================================================*/
#include <stdio.h>  /* printf */
#include <string.h> /* memset */
#include <stdlib.h>

#include "vsa.h"

static void *AllocWriteVerify(vsa_t *vsa, size_t block_size);
static void TestStressLimits(void);
static void TestBlockInsert(void);

int main(void)
{
    TestStressLimits();
    TestBlockInsert();

    return 0;
}

static void *AllocWriteVerify(vsa_t *vsa, size_t block_size)
{
    void *user_block = VSAAlloc(vsa, block_size);

    if (NULL != user_block)
    {
        memset(user_block, 0, block_size);
    }

    return user_block;
}

static void TestStressLimits(void)
{
    void *block_pointers[1500] = { NULL };
    void *buffer = malloc(0x8000 + 1);
    vsa_t *test_allocator = VSAInit(buffer, 0x8000 + 1);
    size_t i = 0;
    void *this_block = AllocWriteVerify(test_allocator, 1);
    void *fail_block = NULL;

    while (NULL != this_block)
    {
        block_pointers[i] = this_block;
        this_block = AllocWriteVerify(test_allocator, 1);
        ++i;
    }

    printf("TestStressLimits processed (should be 1365) %lu blocks\n", i);

    --i;
    while (i > 0)
    {
        VSAFree(block_pointers[i]);
        --i;
    }
    VSAFree(block_pointers[0]);

    this_block = AllocWriteVerify(test_allocator, 0x8000 - 24);

    printf("largest valid block: (this should be valid) %p\n", this_block);

    fail_block = AllocWriteVerify(test_allocator, 1);

    printf("over maximum: (this should be NULL) %p\n", fail_block);

    free(buffer);

}

static void TestBlockInsert(void)
{
    void *buffer = malloc(400);
    void *block_pointers[4] = { NULL };
    void *defrag_tester = NULL;
    vsa_t *test_allocator = VSAInit(buffer, 400);
    size_t i = 0;


    printf("\ninsert between two free'd blocks\n\n");
    printf("alloctor @%p .\noriginal blocks:\n", (void *)test_allocator);

    /* alocate 4 blocks */
    for (; i < 4; ++i)
    {
        block_pointers[i] = VSAAlloc(test_allocator, 50);
        printf("\t%p\n", block_pointers[i]);
    }

    /* free middle two blocks */
    VSAFree(block_pointers[1]);
    VSAFree(block_pointers[2]);

    /* alloc at space between */
    defrag_tester = VSAAlloc(test_allocator, 20);

    printf("this should be @address of second original: \n\t%p\n"
            , defrag_tester);

    defrag_tester = VSAAlloc(test_allocator, 20);

    printf("this should be before third original: \n\t%p\n"
            , defrag_tester);

    free(buffer);
}
