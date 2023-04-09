/*==============================================================================
Data Structures - binary Search Tree
Tests
Dekel Sror
Review - Marcel Binyaminov
RC 1
==============================================================================*/

#include <stdio.h> /* printf */


#include "useful.h" /* ARR_LEN */
#include "bst.h"

#define NUM_TESTS (16)

/* sorting_method for tree handle */
static int BiggerChar (const void *data, const void *tree_data);
/* operation for ForEach */
static int DerPrinterCounter(void *tree_data, void *arg);


static void TestEmpty(bst_t *tree, int exp_res, size_t *passed);

/*
    rationale:
        verify empty tree
        insert shorts to tree
        verify non-empty tree
        show the using ForEach
        find existong data
        not find non-extising data
        remove in loop, going from last valid node to beginning of tree.
        Count on each iteration (would break if remove is wrong)
        verify empty tree
        destroy tree (use valgrind to verify)
*/

int main(void)
{
    bst_t *test = BSTCreate(BiggerChar);
    triter_t iter = { 0 };
    short data_ints[] = { 100, 200, 50, 70, 30, 10, 250, 150, 120 };
    short *putter = data_ints;
    size_t count = 0;
    int res_foreach = 0;
    short to_find = 30;
    size_t passed = 0;


    TestEmpty(test, 1, &passed);


    while (putter < (data_ints + ARR_LEN(data_ints)))
    {
        iter = BSTInsert(test, putter);
        ++putter;
    }

    TestEmpty(test, 0, &passed);

    /* this prints values in-order from first to last (small to large) */
    res_foreach = BSTForEach(BSTBegin(test), BSTEnd(test), DerPrinterCounter, &count);

    if (res_foreach)
    {
        printf("ForEach failed! Test function always returns 0 (!)\n");
    }
    else
    {
        ++passed;
    }

    iter = BSTPrev(BSTEnd(test));

    /* this prints values in-order from last to first (large to small) */
    for (; !BSTIsSameIter(iter, BSTBegin(test)); iter = BSTPrev(iter))
    {
        printf("backwards - node data: %d\n", *(short*)BSTGetData(iter));
    }

    printf("backwards - node data: %d\n", *(short*)BSTGetData(iter));

    if (1 == BSTIsSameIter(iter, BSTBegin(test)))
    {
        ++passed;
    }
    else
    {
        printf("supposed to be at beginning!\n");
    }

    if (to_find == *(short *)BSTGetData(BSTFind(test, &to_find)))
    {
        ++passed;
    }
    else
    {
        printf("failed to find!\n");
    }

    to_find = 66;

    if (1 == BSTIsSameIter((BSTFind(test, &to_find)), BSTEnd(test)))
    {
        ++passed;
    }
    else
    {
        printf("failed to NOT find!\n");
    }

    while (!BSTIsEmpty(test))
    {
        passed += (count == BSTCount(test));
        iter = BSTRemove(iter);
        --count;
    }

    TestEmpty(test, 1, &passed);
    BSTDestroy(test);

    printf("out of %d tests, passed %lu\n", NUM_TESTS, passed);

    return 0;
}

static void TestEmpty(bst_t *tree, int exp_res, size_t *passed)
{
    int res = BSTIsEmpty(tree);

    if (res != exp_res)
    {
        printf("empty exp_res %d, had %d\n", exp_res, res);
    }
    else
    {
        ++*passed;
    }
}

static int BiggerChar (const void *data, const void *tree_data)
{
    return *(short *)data - *(short *)tree_data;
}

static int DerPrinterCounter(void *tree_data, void *arg)
{
    ++*(size_t *)arg;
    printf("in-order: [%lu]: %d\n", *(size_t *)arg, *(short *)tree_data);

    return 0;
}
