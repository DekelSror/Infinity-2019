#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "queue.h"
#include "sorts.h"
#include "heap.h"

#define UNUSED(x) ((void)x)

/* MergeSort utility functions */
static void MergeSubArrs(int *arr, int *buffer, size_t start, size_t end);
static void MSort(int *arr, int *buffer, size_t start, size_t end);

/* HeapSort utility functions */
static void HeapifyUp(int *arr, size_t index);
static void HeapyifyDown(int *arr, size_t index, size_t heap_last);
static void Swap(int *num_1, int *num_2);

void InsertionSort(int *arr, size_t len)
{
    const int *end = arr + len;
    int *p_index = arr + 1;

    while (p_index < end)
    {
        int *p_swap = p_index;

        while ((arr < p_swap) && (*(p_swap - 1) > *(p_swap)))
        {
            int tmp = *(p_swap - 1);
            *(p_swap - 1) = *p_swap;
            *p_swap = tmp;
            --p_swap;
        }

        ++p_index;
    }
}

void SelectionSort(int *arr, size_t len)
{
    const int *end = arr + len;
    int *new_start = arr;
    int tmp = 0;

    while (new_start < end)
    {
        int *runner = new_start;
        int *min = new_start;

        while (end > runner)
        {
            if (*runner < *min)
            {
                min = runner;
            }

            ++runner;
        }

        tmp = *(new_start);
        *new_start = *min;
        *min = tmp;
        ++new_start;
    }
}

void BubbleSort(int *arr, size_t len)
{
    int *new_end = arr + len;
    int *start = arr + 1;
    int working = 1;

    while (working)
    {
        working = 0;
        start = arr + 1;

        while (start < new_end)
        {
            if (*(start - 1) > *(start))
            {
                int tmp = *start;
                *start = *(start - 1);
                *(start - 1) = tmp;
                working = 1;
            }

            ++start;
        }

        --new_end;
    }
}

void CountingSort(int *arr, size_t len, size_t range)
{
    int *count_lut = calloc(range, sizeof(int));
    int *res_arr = calloc(len, sizeof(int));
    int *p_arr = arr;
    size_t i = 0;

    for (i = 0; i < len; ++i)
    {
        ++count_lut[*p_arr];
        ++p_arr;
    }

    p_arr = res_arr;

    for (i = 0; i < range; ++i)
    {
        size_t duplicates = count_lut[i];

        while (0 < duplicates)
        {
            *p_arr = i;
            ++p_arr;
            --duplicates;
        }
    }

    memcpy(arr, res_arr, sizeof(int) * len);

    free(res_arr);
    res_arr = NULL;

    free(count_lut);
    count_lut = NULL;
}

void RadixSort(int *arr, size_t len, size_t digits)
{
    size_t bucket_index = 0;
    queue_t *buckets[10] = { NULL };
    int *p_arr = arr;
    size_t exponent = 1;
    int *res_arr = calloc(len, sizeof(int));
    const int *arr_end = arr + len;

    for (bucket_index = 0; bucket_index < 10; ++bucket_index)
    {
        buckets[bucket_index] = QCreate();
    }

    for (; 0 < digits; --digits)
    {
        for (p_arr = arr; p_arr < arr_end; ++p_arr)
        {
            int num_to_bucket = *p_arr / exponent % 10;

            QEnqueue(buckets[num_to_bucket], p_arr);
        }

        p_arr = res_arr;

        for (bucket_index = 0; bucket_index < 10; ++bucket_index)
        {
            while (!QIsEmpty(buckets[bucket_index]))
            {
                *p_arr = *(int *)QPeek(buckets[bucket_index]);
                ++p_arr;
                QDequeue(buckets[bucket_index]);
            }
        }

        exponent *= 10;
        memcpy(arr, res_arr, len * sizeof(int));
    }

    for (bucket_index = 0; bucket_index < 10; ++bucket_index)
    {
        QDestroy(buckets[bucket_index]);
    }

    free(res_arr);
    res_arr = NULL;
}

void MergeSort(int *arr, size_t len)
{
    int *res_arr = calloc(len, sizeof(int));

    MSort(arr, res_arr, 0, len);

    memcpy(arr, res_arr, len * sizeof(int));

    free(res_arr);
    res_arr = NULL;
}

void HeapSort(int *arr, size_t len)
{
    size_t i = 0;

    /* no use to HeapifyUp arr[0] */
    for (i = 1; i < len; ++i)
    {
        HeapifyUp(arr,i);
    }

    for (i = 0; i < len; ++i)
    {
        Swap(&arr[0], &arr[len - i - 1]);
        HeapyifyDown(arr, 0, len - i - 1);
    }
}


static void MSort(int *arr, int *buffer, size_t start, size_t end)
{
    if (end - start > 1)
    {
        size_t middle = (start + end) / 2;

        MSort(arr, buffer, start, middle);
        MSort(arr, buffer, middle, end);
        MergeSubArrs(arr, buffer, start, end);
    }
}

static void MergeSubArrs(int *arr, int *buffer, size_t start, size_t end)
{
    const int *mid_point = arr + ((start + end) / 2);
    const int *end_point = arr + end;
    int *p_start = arr + start;
    int *p_middle = (int *)mid_point;
    int *buffer_write_spot = buffer + start;

    while ((p_start < mid_point) && (p_middle < end_point))
    {
        if (*p_start < *p_middle)
        {
            *buffer_write_spot = *p_start;
            ++p_start;
        }
        else
        {
            *buffer_write_spot = *p_middle;
            ++p_middle;
        }

        ++buffer_write_spot;
    }

    while (p_start < mid_point)
    {
        *buffer_write_spot = *p_start;
        ++p_start;
        ++buffer_write_spot;
    }

    while (p_middle < end_point)
    {
        *buffer_write_spot = *p_middle;
        ++p_middle;
        ++buffer_write_spot;
    }

    memcpy((arr + start), buffer + start, (end - start) * sizeof(int));
}

static void HeapifyUp(int *arr, size_t index)
{
    if (0 == index)
    {
        return;
    }
    else if(arr[index] > arr[(index-1)/2])
    {
        Swap(&arr[index], &arr[(index-1)/2]);
        HeapifyUp(arr, (index-1)/2);
    }
}

static void HeapyifyDown(int *arr, size_t index, size_t heap_last)
{
    size_t i_right = index * 2 + 2;
    size_t i_left = i_right - 1;
    int i_max_child = i_left;

    if  (i_left >= heap_last)
    {
        return;
    }

    else if (i_right < heap_last)
    {
        if (arr[i_right] > arr[i_left])
        {
            i_max_child = i_right;
        }
    }

    if (arr[index] < arr[i_max_child])
    {
        Swap(&arr[index], &arr[i_max_child]);
        HeapyifyDown(arr, i_max_child, heap_last);
    }
}

static void Swap(int *num_1, int *num_2)
{
    int swap = 0;


    swap = *num_1;
    *num_1 = *num_2;
    *num_2 = swap;
}

/* for debugging purposes */
void FirstN(int *arr, size_t n)
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
