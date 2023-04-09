/*==============================================================================
Data Structures - Stack
Tests
Dekel Sror
Review - Moti Zamir
RC 1
==============================================================================*/

#include <stdio.h> /* printf */

#include "vector.h"

#define TEST_LENGTH (8192) /* desired total elements in vector */

/* TODO : set hard-coded values as macros. Use pow to get capacity */

static size_t TestExtendScenario(void);

static int TestCapacity  (vector_t *test, size_t exp_res);
static int TestVectorSize(vector_t *test, size_t exp_res);
static int TestVectorPush(vector_t *test, const void *item, int exp_res);

int main(void)
{
    size_t total_successes = TestExtendScenario();

    printf("%lu successful tests!\n", total_successes);

    return 0;
}

static size_t TestExtendScenario(void)
{
    size_t i = 0;
    size_t success = 0;

    vector_t *test = VectorCreate(sizeof(size_t), 5);

    success += TestVectorSize(test, 0);
    success += TestCapacity(test, 5);

    for (i = 0; i < TEST_LENGTH; ++i)
    {
        size_t to_push = i;
        success += TestVectorSize(test, i);
        success += TestVectorPush(test, &to_push, 0);
    }

    success += TestVectorSize(test, 8192);
    success += TestCapacity(test, 10240);

    for (i = 0; i < TEST_LENGTH; ++i)
    {
        success += i == *(size_t*)VectorGet(test, i);
    }

    success += 0 == VectorResize(test, 20);

    success += TestVectorSize(test, 20);
    success += TestCapacity(test, 20);

    for (i = 20; i > 0; --i)
    {
        VectorPop(test);
        success += i == *(size_t*)VectorGet(test, i - 1);
    }

    success += TestVectorSize(test, 0);
    VectorDestroy(test);

    return success;
}

static int TestVectorSize(vector_t *test, size_t exp_res)
{
    size_t res = VectorSize(test);

    if (exp_res != res)
    {
        printf("VectorSize failed, had %lu, exp_res %lu\n", res, exp_res);

        return 0;
    }

    return 1;
}

static int TestCapacity(vector_t *test, size_t exp_res)
{
    size_t res = VectorCapacity(test);

    if (exp_res != res)
    {
        printf("Capacity failed, had %lu, exp_res %lu\n", res, exp_res);

        return 0;
    }

    return 1;
}

static int TestVectorPush(vector_t *test, const void *item, int exp_res)
{
    int res = VectorPush(test, item);

    if (exp_res != res)
    {
        printf("VectorPush failed! errcode %d\n", res);

        return 0;
    }

    return 1;
}
