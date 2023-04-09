#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

#include "sorts.h"

#define TEST_SIZE (20lu)


void TestSortVsQSort(const char *name, void(*sort)(int *, size_t),
                    int *test, int *sys, size_t len);

void TestCountVsQSort(int *test, int *sys, size_t len, size_t range);
void TestRadixVsQSort(int *test, int *sys, size_t len, size_t radix);

void RandFillBoth(int *arr1, int *arr2, size_t len);
void RangeRandFillBoth(int *arr1, int *arr2, size_t len, size_t range);

/* argument to qsort */
int FQSort(const void *first, const void *second);

int main(void)
{
    int test_arr[TEST_SIZE] = { 0 };
    int qsort_arr[TEST_SIZE] = { 0 };

    printf("sorts. test array size: %lu\n\n", TEST_SIZE);
/*
    RandFillBoth(test_arr, qsort_arr, TEST_SIZE);
    TestSortVsQSort("InsertionSort", InsertionSort, test_arr, qsort_arr,
                    TEST_SIZE);


    RandFillBoth(test_arr, qsort_arr, TEST_SIZE);
    TestSortVsQSort("SelectionSort", SelectionSort, test_arr, qsort_arr,
                    TEST_SIZE);


    RandFillBoth(test_arr, qsort_arr, TEST_SIZE);
    TestSortVsQSort("BubbleSort", BubbleSort, test_arr, qsort_arr,
                    TEST_SIZE);
    RangeRandFillBoth(test_arr, qsort_arr, TEST_SIZE, 0x1000);
    TestCountVsQSort(test_arr, qsort_arr, TEST_SIZE, 0x1000);

    RangeRandFillBoth(test_arr, qsort_arr, TEST_SIZE, 10000);
    TestRadixVsQSort(test_arr, qsort_arr, TEST_SIZE, 4);



    RandFillBoth(test_arr, qsort_arr, TEST_SIZE);
    TestSortVsQSort("MergeSort", MergeSort, test_arr, qsort_arr, TEST_SIZE);

    RandFillBoth(test_arr, qsort_arr, TEST_SIZE);
    TestSortVsQSort("HeapSort", HeapSort, test_arr, qsort_arr, TEST_SIZE);
*/

/*
    printf("arrays are now sorted. testing...\n");

    TestSortVsQSort("SelectionSort", SelectionSort, test_arr, qsort_arr,
                    TEST_SIZE);
    TestSortVsQSort("InsertionSort", InsertionSort, test_arr, qsort_arr,
                    TEST_SIZE);
    TestSortVsQSort("BubbleSort", BubbleSort, test_arr, qsort_arr,
                    TEST_SIZE);
*/
    return 0;
}

void TestSortVsQSort(const char *name, void(*sort)(int *, size_t),
                    int *test, int *sys, size_t len)
{
    int res = 0;
    clock_t timer = { 0 };

    timer = clock();

    qsort(sys, TEST_SIZE, sizeof(int), FQSort);

    timer = difftime(clock(), timer);

    printf("%s. qsort did it in: %lu ticks\n", name, timer);

    timer = clock();

    sort(test, TEST_SIZE);

    timer = difftime(clock(), timer);

    printf("%s. we did it in: %lu ticks\n", name, timer);

    res = memcmp(sys, test, sizeof(int) * len);

    if (0 != res)
    {
        printf("memcpy had :%d\n\n\n", res);
        First100(test);
        First100(sys);
    }
    else
    {
        printf("%s successful!\n", name);
    }
}

void TestCountVsQSort(int *test, int *sys, size_t len, size_t range)
{
    int res = 0;
    clock_t timer = { 0 };

    timer = clock();

    qsort(sys, len, sizeof(int), FQSort);

    timer = difftime(clock(), timer);

    printf("CountingSort. qsort did it in: %lu ticks\n", timer);

    timer = clock();

    CountingSort(test, len, range);

    timer = difftime(clock(), timer);

    printf("CountingSort. we did it in: %lu ticks\n", timer);

    res = memcmp(sys, test, sizeof(int) * len);

    if (0 != res)
    {
        printf("%d\n\n\n", res);
        First100(test);
        First100(sys);
    }
    else
    {
        printf("CountingSort successful!\n");
    }
}

void TestRadixVsQSort(int *test, int *sys, size_t len, size_t radix)
{
    int res = 0;

    clock_t timer = { 0 };

    timer = clock();

    qsort(sys, len, sizeof(int), FQSort);

    timer = difftime(clock(), timer);

    printf("RadixSort. qsort did it in: %lu ticks\n", timer);

    timer = clock();

    RadixSort(test, len, radix);

    timer = difftime(clock(), timer);

    printf("RadixSort. we did it in: %lu ticks\n", timer);

    res = memcmp(sys, test, sizeof(int) * len);

    if (0 != res)
    {
        printf("no good %d\n\n\n", res);
        First100(test);
        First100(sys);
    }
    else
    {
        printf("RadixSort successful\n");
    }
}

void RandFillBoth(int *arr1, int *arr2, size_t len)
{
    int *p_assign = arr1;
    size_t i = 0;

    srand(getpid() / 2 + 14);

    for (i = 0; i < len; ++i)
    {
        *p_assign = rand();
        ++p_assign;
    }

    memcpy(arr2, arr1, sizeof(int) * len);
}

void RangeRandFillBoth(int *arr1, int *arr2, size_t len, size_t range)
{
    int *p_assign = arr1;
    size_t i = 0;

    srand(getpid());

    for (i = 0; i < len; ++i)
    {
        *p_assign = rand() % range;
        ++p_assign;
    }

    memcpy(arr2, arr1, sizeof(int) * len);
}

int FQSort(const void *first, const void *second)
{
    return *(int *)first > *(int *)second;
}
