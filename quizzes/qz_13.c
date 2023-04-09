/*
Quiz #13 - add adjacent ints in array, in-place, into longs
assume even length for array
*/

#include <stddef.h> /* NULL, size_t */
#include <stdio.h> /* printf */
#include <string.h> /* memcmp */

#define ARR_LEN(x) (sizeof(x) / sizeof(x[0]))

long *SumIntsToLongs(int *arr, size_t len);

static int test_arr[] = { 1, -2, 3, -4, 5, -6 };
static const long exp_arr[] = { -1l, -1l, -1l };

int main(void)
{
    long *res = SumIntsToLongs(test_arr, ARR_LEN(test_arr));

    if (memcmp(res, exp_arr, sizeof(long) * ARR_LEN(exp_arr)))
    {
        printf("failed\n");
    }

    return 0;
}


long *SumIntsToLongs(int *arr, size_t len)
{
    long adder = 0l;
    long *arr_long = NULL;
    size_t i = 0;
    int *p_arr = arr;

    for (i = 0; i < (len / 2); ++i)
    {
        adder = (long)*p_arr + (long)*(p_arr + 1);
        arr_long = (long *)p_arr;
        *arr_long = adder;
        p_arr += 2;
    }

    return (long *)arr;
}
