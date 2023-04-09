/*========================================================================*/
/* Quiz #9                                                                */
/* Dynamic Programming                                                    */
/* MaxSubArr. advanced - no assumptions                                   */
/* Dekel Sror */
/*========================================================================*/

#include <stdio.h> /* printf */
#include <stdlib.h>
#include <assert.h>

#define MAX2(a, b) (a > b ? a : b)

typedef struct subarr
{
    size_t start;
    size_t end;
    int    sum;
}subarr;

static void   ArrPrint        (const int arr[], size_t len);
static subarr MaxSubArrAllNega(const int arr[], size_t len);

/* test data */
static const int test_1[] = { -6, -7, 8, -8, 8, 1, 9, -54, 15 };
static const int test_2[] = { -2, -90, -14, -4, -5, -3, -5, -600 };

int main(void)
{
    subarr tarr = MaxSubArrAllNega(test_1, 9);

    printf("for input :");
    ArrPrint(test_1, 9);
    printf("result:\n\tstart: %lu end: %lu sum: %d\n", tarr.start, tarr.end, tarr.sum);

    printf("========================================================================\n");

    tarr = MaxSubArrAllNega(test_2, 8);

    printf("for input :");
    ArrPrint(test_2, 8);
    printf("result:\n\tstart: %lu end: %lu sum: %d\n", tarr.start, tarr.end, tarr.sum);

    return 0;
}


/* generalized for all negative values */
subarr MaxSubArrAllNega(const int arr[], size_t len)
{
    int sum_candidate = 0;
    size_t i = 0;
    subarr res = { 0, 0, 0 };
    int chunk_start = 0;

    assert(arr);

    res.sum = arr[0];

    for (i = 0; i < len; ++i)
    {
        sum_candidate += arr[i];

        if (sum_candidate <= arr[i])
        {
            sum_candidate = arr[i];
            chunk_start = i + 1;
        }

        if (sum_candidate > res.sum)
        {
            res.sum = sum_candidate;
            res.start = chunk_start;
            res.end = i;
        }
    }

    return res;
}

void ArrPrint(const int arr[], size_t len)
{
    size_t i = 0;

    printf("\n[ ");
    for (i = 0; i < len; ++i)
    {
        printf("%d,  ", arr[i]);
        if (0 == (i + 1) % 10)
        {
            printf("\n");
        }
    }
    printf(" ]\n");
}
