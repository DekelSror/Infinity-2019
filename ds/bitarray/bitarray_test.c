/*==============================================================================
Data Structures - Bit Array
Tests
Dekel Sror
Review - Jenia Taranov
RC 2
==============================================================================*/

#include <stdio.h> /* printf */

#include "bitarray.h"

/* constants for tests */
#define BIT_63    (0x8000000000000000)
/* postfix _H meaning 1010 instead of 0101 */
#define MASK_1_H  (0xaaaaaaaaaaaaaaaa)
#define MASK_4_H  (0xf0f0f0f0f0f0f0f0)
static const size_t s_t_1 = 1;
static const size_t s_t_0 = 0;

/* functions in module are of 4 types */
/* each type has a testrun and a test function */
static size_t TestRunOnOffRot(void);
static size_t TestRunSet(void);
static size_t TestRunIs(void);
static size_t TestRunAllMirrorCount(void);

static size_t TestAllMirrorCount(size_t arr, size_t exp_res,
                                 size_t(*ba_func)(size_t));

static size_t TestSetOnOffRot(size_t arr, size_t index, size_t exp_res,
                              size_t(*ba_func)(size_t, size_t));

static int    TestIs(size_t arr, size_t index, int exp_res,
                     int(*ba_func)(size_t, size_t));

static size_t TestSetBit(size_t arr, size_t index, int value, size_t exp_res,
                         size_t(*ba_func)(size_t, size_t, int));

int main(void)
{
    size_t total_tests = 0;

    total_tests += TestRunIs();
    total_tests += TestRunSet();
    total_tests += TestRunOnOffRot();
    total_tests += TestRunAllMirrorCount();

    printf("%lu successful_tests\n", total_tests);

    return 0;
}
/* here we call the test function with different parameters */
/* and accumulate successes */
static size_t TestRunSet(void)
{
    size_t successful_tests = 0;

    successful_tests += TestSetBit(s_t_0, 8, 1, (size_t)256, BitArraySetBit);
    successful_tests += TestSetBit(s_t_0, 8, 0, s_t_0, BitArraySetBit);
    successful_tests += TestSetBit(MASK_1, 0, 1, MASK_1, BitArraySetBit);
    successful_tests += TestSetBit(MASK_1, 1, 1, MASK_1 + 2, BitArraySetBit);

    return successful_tests;
}

static size_t TestRunIs(void)
{
    size_t successful_tests = 0;

    successful_tests += TestIs(s_t_0, s_t_0, 0, BitArrayIsOn);
    successful_tests += TestIs(s_t_1, s_t_0, 1, BitArrayIsOn);
    successful_tests += TestIs(BIT_63, (size_t)(63), 1, BitArrayIsOn);
    successful_tests += TestIs(s_t_0, (size_t)(10), 1, BitArrayIsOff);
    successful_tests += TestIs((size_t)(16), s_t_0, 1, BitArrayIsOff);
    successful_tests += TestIs((size_t)(255), (size_t)(5), 0, BitArrayIsOff);

    return successful_tests;
}

static size_t TestRunAllMirrorCount(void)
{
    size_t successful_tests = 0;

    successful_tests += TestAllMirrorCount(MASK_1, ULONG_MAX, BitArrayAllOn);
    successful_tests += TestAllMirrorCount(MASK_1, s_t_0, BitArrayAllOff);

    successful_tests += TestAllMirrorCount(MASK_1, MASK_1_H, BitArrayMirrorBytes);
    successful_tests += TestAllMirrorCount(s_t_1, (size_t)128, BitArrayMirrorBytes);
    successful_tests += TestAllMirrorCount(MASK_4, MASK_4_H, BitArrayMirrorBytes);

    successful_tests += TestAllMirrorCount(MASK_1, 32, BitArrayCountOn);
    successful_tests += TestAllMirrorCount(ULONG_MAX - 2, 63, BitArrayCountOn);

    successful_tests += TestAllMirrorCount(MASK_1, 32, BitArrayCountOff);
    successful_tests += TestAllMirrorCount(s_t_0, 64, BitArrayCountOff);

    successful_tests += TestAllMirrorCount(MASK_1, 32, BitArrayCountOnLUT);
    successful_tests += TestAllMirrorCount(BIT_63, 1, BitArrayCountOnLUT);
    successful_tests += TestAllMirrorCount(ULONG_MAX, 64, BitArrayCountOnLUT);

    successful_tests += TestAllMirrorCount(MASK_1, MASK_1_H, BitArrayMirrorBytesLUT);
    successful_tests += TestAllMirrorCount(s_t_1, (size_t)128, BitArrayMirrorBytesLUT);


    return successful_tests;
}

static size_t TestRunOnOffRot(void)
{
    size_t successful_tests = 0;

    successful_tests += TestSetOnOffRot(s_t_0, s_t_0, s_t_1, BitArraySetOn);
    successful_tests += TestSetOnOffRot(s_t_1, s_t_1, (size_t)(3), BitArraySetOn);
    successful_tests += TestSetOnOffRot((size_t)(254), s_t_0, (size_t)(255), BitArraySetOn);

    successful_tests += TestSetOnOffRot(s_t_1, s_t_0, s_t_0, BitArraySetOff);
    successful_tests += TestSetOnOffRot((size_t)(2), s_t_0, (size_t)(2), BitArraySetOff);
    successful_tests += TestSetOnOffRot(BIT_63, (size_t)(63), s_t_0, BitArraySetOff);

    successful_tests += TestSetOnOffRot(MASK_1, 40, MASK_1, BitArrayRotateLeft);
    successful_tests += TestSetOnOffRot(s_t_1, 0, s_t_1, BitArrayRotateLeft);
    successful_tests += TestSetOnOffRot(BIT_63, 1, s_t_1, BitArrayRotateLeft);

    successful_tests += TestSetOnOffRot(BIT_63, 1, BIT_63 / 2, BitArrayRotateRight);

    successful_tests += TestSetOnOffRot(MASK_1, 9, MASK_1_H, BitArrayRotateLeft);
    successful_tests += TestSetOnOffRot(MASK_1, 2, MASK_1, BitArrayRotateRight);

    successful_tests += TestSetOnOffRot(s_t_1, 0, s_t_0, BitArrayFlipBit);
    successful_tests += TestSetOnOffRot(s_t_1, 2, (size_t)5, BitArrayFlipBit);
    successful_tests += TestSetOnOffRot(BIT_63, 0, BIT_63 + 1, BitArrayFlipBit);
    successful_tests += TestSetOnOffRot(BIT_63, 63, s_t_0, BitArrayFlipBit);

    return successful_tests;
}

/* test functions - returns 1 or 0 and report to stdout */
static int TestIs(size_t arr, size_t index, int exp_res,
                    int(*ba_func)(size_t, size_t))
{
    if (exp_res == ba_func(arr, index))
    {
        return 1;
    }
    printf("TestIs failed! input %lx, index %lu, exp_res %d\n"
                , arr, index, exp_res);
    return 0;
}

static size_t TestSetOnOffRot(size_t arr, size_t index, size_t exp_res,
                      size_t(*ba_func)(size_t, size_t))
{
    if (exp_res == ba_func(arr, index))
    {
        return 1;
    }
    printf("TestSetOnOffRot failed! input %lx, index %lu exp_res %lx\n"
                , arr, index, exp_res);
    return 0;
}

static size_t TestAllMirrorCount(size_t arr, size_t exp_res,
                                 size_t(*ba_func)(size_t))
{
    if (exp_res == ba_func(arr))
    {
        return 1;
    }
    printf("TestAllMirrorCount failed! input %lx, exp_res %lx\n"
                , arr, exp_res);
    return 0;
}

static size_t TestSetBit(size_t arr, size_t index, int value, size_t exp_res,
                        size_t(*ba_func)(size_t, size_t, int))
{
    if (exp_res == ba_func(arr, index, value))
    {
        return 1;
    }
    printf("TestSetBit failed! input %lx, index %lu, value %d, exp_res %lx\n"
                , arr, index, value, exp_res);
    return 0;
}
