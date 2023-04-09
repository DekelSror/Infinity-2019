#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>

#include "quick_sort.h"

#define TEST_SIZE (500)

static int FQSort(const void *first, const void *second);
static void RangeRandFillBoth(int *arr1, int *arr2, size_t len, size_t range);
static void TestQuickSort(int *my_buffer, int *vs_buffer, size_t len);
static void TestBSearch(int *buffer, int search_index);
static void FirstN(int *arr, size_t n);

int main(void)
{
    static int my_buffer[TEST_SIZE] = { 0 };
    static int vs_buffer[TEST_SIZE] = { 0 };

    RangeRandFillBoth(my_buffer, vs_buffer, TEST_SIZE, 100);

    TestQuickSort(my_buffer, vs_buffer, TEST_SIZE);

    TestBSearch(my_buffer, 6);
    TestBSearch(my_buffer, 499);
    TestBSearch(my_buffer, 206);
    TestBSearch(my_buffer, 340);

    return 0;
}

static void TestBSearch(int *buffer, int search_index)
{
    int *bsearch_res = (int *)BinarySearch(buffer, TEST_SIZE, sizeof(int),
                                        FQSort, &buffer[search_index]);

    if (NULL == bsearch_res)
    {
        printf("failed to find %d in array\n", buffer[search_index]);
    }
}

static void TestQuickSort(int *my_buffer, int *vs_buffer, size_t len)
{
    int res = 0;
    clock_t timer =  0;

    timer = clock();

    qsort(vs_buffer, TEST_SIZE, sizeof(int), FQSort);

    timer = clock() - timer;

    printf("system qsort did it in: %lu ticks\n",timer);

    timer = clock();

    QuickSort(my_buffer, TEST_SIZE, sizeof(int), FQSort);

    timer = clock() -  timer;

    printf("Our QuickSort did it in: %lu ticks\n",timer);

    res = memcmp(vs_buffer, my_buffer, sizeof(int) * len);

    if (0 != res)
    {
        printf("memcpy had :%d\n\n\n", res);
        FirstN(my_buffer, TEST_SIZE);
        FirstN(vs_buffer, TEST_SIZE);
    }
    else
    {
        printf("QuickSort successful!\n");
    }
}

static void RangeRandFillBoth(int *arr1, int *arr2, size_t len, size_t range)
{
    int *p_assign = arr1;
    size_t i = 0;

    for (i = 0; i < len; ++i)
    {
        *p_assign = rand() % range;
        ++p_assign;
    }

    memcpy(arr2, arr1, sizeof(int) * len);
}

static int FQSort(const void *first, const void *second)
{
    return *(int *)first - *(int *)second;
}

static void FirstN(int *arr, size_t n)
{
    size_t i = 0;

    for (i = 0; i < n; ++i)
    {
        if (0 == (i % 5))
        {
            printf("\n");
        }
        printf("[%lu]:%d ", i, arr[i]);
    }

    printf("\n\n");
}
