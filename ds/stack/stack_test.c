/*==============================================================================
Data Structures - Stack
Tests
Dekel Sror
Review - Tzvi Cubac
RC 1
==============================================================================*/

#include <stdio.h> /* printf */
#include <string.h> /* memcpy */
#include "stack.h"

#define ARR_LEN(x) (sizeof(x) / sizeof(x[0]))
static size_t TestFloatData(void);
static size_t TestSizeTData(void);

static int TestSize(stack_t *st, size_t exp_res);
static int TestPeekFloat(stack_t *st, float exp_res);
static int TestPeekSizeT(stack_t *st, size_t exp_res);


/* add or remove values from these at will */
static const size_t data_s_t[] = { 654, 55454, 0, 1, 2, 0, 3, 4, 0, 1, 8, 7777 };
static const float data_float[] = { 1.5,26.8, 3.1415296, 1.1618, -40.3, -20000, -3E-5, 2.718};

int main(void)
{
    size_t total_tests = 0;

    total_tests += TestSizeTData();
    total_tests += TestFloatData();

    printf("%lu successes\n", total_tests);

    return 0;
}

static size_t TestSizeTData(void)
{
    stack_t *test = StackCreate(sizeof(size_t), ARR_LEN(data_s_t));
    size_t i = 0;
    size_t successes = 0;

    successes += TestSize(test, 0);

    for (i = 0; i < ARR_LEN(data_s_t); ++i)
    {
        successes += TestSize(test, i);
        StackPush(test, &(data_s_t[i]));
        successes += TestPeekSizeT(test, data_s_t[i]);
    }

    for (i = ARR_LEN(data_s_t); i > 0 ; --i)
    {
        successes += TestSize(test, i);
        successes += TestPeekSizeT(test, data_s_t[i -1]);
        StackPop(test);
    }

    successes += TestSize(test, 0);
    StackDestroy(test);

    return successes;
}

static size_t TestFloatData(void)
{
    stack_t *test = StackCreate(sizeof(float), ARR_LEN(data_float));
    size_t i = 0;
    size_t successes = 0;

    successes += TestSize(test, 0);

    for (i = 0; i < ARR_LEN(data_float); ++i)
    {
        successes += TestSize(test, i);
        StackPush(test, &(data_float[i]));
        successes += TestPeekFloat(test, data_float[i]);
    }

    for (i = ARR_LEN(data_float); i > 0 ; --i)
    {
        successes += TestSize(test, i);
        successes += TestPeekFloat(test, data_float[i - 1]);
        StackPop(test);
    }

    successes += TestSize(test, 0);

    StackDestroy(test);

    return successes;
}


static int TestPeekSizeT(stack_t *st, size_t exp_res)
{
    size_t res = *(size_t*)StackPeek(st);

    if (exp_res != res)
    {
        printf("TestPeekSizeT failed! had %lu, exp_res %lu\n", res, exp_res);
        return 0;
    }

    return 1;
}

static int TestSize(stack_t *st, size_t exp_res)
{
    size_t res = StackSize(st);

    if (exp_res != res)
    {
        printf("TestSize failed! had %lu, exp_res %lu\n", res, exp_res);
        return 0;
    }

    return 1;
}

static int TestPeekFloat(stack_t *st, float exp_res)
{
    float res = *(float*)StackPeek(st);

    if (exp_res != res)
    {
        printf("TestPeekFloat failed! had %f, exp_res %f\n", res, exp_res);
        return 0;
    }

    return 1;
}
