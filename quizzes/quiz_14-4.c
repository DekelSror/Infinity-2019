/*
Dekel Sror
Quiz  - SumPairsIntToLong
*/

#include <stdio.h> /* printf */
#include <string.h> /* memcmp to test */
#include <stddef.h> /* size_t */
#include <assert.h> /* assert */
#include <limits.h> /* INT_MAX, INT_MIN */

#define ARR_LEN(x) (sizeof(x) /sizeof(x[0]))

static long *SumPairsIntToLong(int *arr, size_t len);
static int TestSPITL(int *test, const long *res, size_t len);
static void LongArrPrint(const long *to_print, size_t len);


static int test_arr_1[] = { -6, 8, 20, -16 ,3, 3 };
static const long res_arr_1[] = { 2, 4, 6 };

static int test_arr_2[] = { 0, 0 };
static const long res_arr_2[] = { 0 };

static int test_arr_3[] = { INT_MAX, 400, INT_MIN, INT_MAX, INT_MIN, INT_MIN };
static const long res_arr_3[] = { (long)INT_MAX + 400, -1, (long)INT_MIN * 2};

int main(void)
{
    int suc = 0;

    suc += TestSPITL(test_arr_1, res_arr_1, ARR_LEN(test_arr_1));
    suc += TestSPITL(test_arr_2, res_arr_2, ARR_LEN(test_arr_2));
    suc += TestSPITL(test_arr_3, res_arr_3, ARR_LEN(test_arr_3));

    printf("successess: %d\n", suc);

    return 0;
}

static int TestSPITL(int *test, const long *res, size_t len)
{
    long *p_test = SumPairsIntToLong(test, len);

    if (memcmp(test, res, len * sizeof(int)))
    {
        printf("failed to sum ints to longs :(\n");
        printf("you had: \t");
        LongArrPrint((long *)test, len / 2);
        printf("wanted: \t");
        LongArrPrint(res, len / 2);
        return 0;
    }

/* rid of warning */
    (void)p_test;

    return 1;
}

/* assumes len is even */
static long *SumPairsIntToLong(int *arr, size_t len)
{
    int *p_arr_int = arr;
    long *p_arr_long = (long *)arr;

    assert(arr);

    while (p_arr_int < (arr + len))
    {
        *p_arr_long = (long)*(p_arr_int) + (long)*(p_arr_int + 1);
        p_arr_int += 2;
        ++p_arr_long;
    }

    return (long *)arr;
}

static void LongArrPrint(const long *to_print, size_t len)
{
    const long *p_long = to_print;

    while (p_long < (to_print + len))
    {
        printf("%ld,", *p_long);
        ++p_long;
    }

    printf("\n\n");
}
