#include "quick_sort.h"

#define WORD_SIZE (sizeof(void *))

static void MemSwap(char *arr, size_t element_size,
    size_t index_1, size_t index_2);

static size_t Partition(char *arr, size_t left, size_t right,
    size_t element_size, compar_t compar);

static void QSort(char *arr, size_t left, size_t right,
    size_t element_size,
    compar_t compar);

static void *BSearch(char *arr, size_t start, size_t end, size_t element_size,
    compar_t compar, const void *to_seek);

void QuickSort(void *arr, size_t nmemb,
    size_t element_size,
    compar_t compar)
{
    QSort(arr, 0, nmemb, element_size, compar);
}

void *BinarySearch(void *arr, size_t nmemb, size_t element_size,
    compar_t compar, const void *to_seek)
{
    return BSearch(arr, 0, nmemb, element_size, compar, to_seek);
}

static void QSort(char *arr, size_t left, size_t right,
    size_t element_size,
    compar_t compar)
{
    if (left < right)
    {
        size_t pivot_index = Partition(arr, left, right - 1, element_size, compar);

        QSort(arr, left, pivot_index, element_size, compar);
        QSort(arr, pivot_index + 1, right, element_size, compar);
    }
}

static size_t Partition(char *arr, size_t left, size_t right,
    size_t element_size,
    compar_t compar)
{
    size_t pivot_index = left;

    for (; left < right; ++left)
    {
         if (0 >= compar(arr + (left * element_size), arr + (right * element_size)))
        {
            MemSwap(arr, element_size, left, pivot_index);
            ++pivot_index;
        }
    }

    MemSwap(arr, element_size, pivot_index, right);

    return pivot_index;
}

static void MemSwap(char *arr, size_t element_size,
    size_t index_1,
    size_t index_2)
{
    char *byte_move_1 = NULL;
    char *byte_move_2 = NULL;

    size_t *word_move_1 = (size_t *)(arr + (index_1 * element_size));
    size_t *word_move_2 = (size_t *)(arr + (index_2 * element_size));

    while (WORD_SIZE <= element_size)
    {
        size_t word_swap = *word_move_1;
        *word_move_1 = *word_move_2;
        *word_move_2 = word_swap;
        ++word_move_1;
        ++word_move_2;
        element_size -= WORD_SIZE;
    }

    byte_move_1 = (char *)word_move_1;
    byte_move_2 = (char *)word_move_2;


    while (0 < element_size)
    {
        char byte_swap = *byte_move_1;
        *byte_move_1 = *byte_move_2;
        *byte_move_2 = byte_swap;

        ++byte_move_1;
        ++byte_move_2;

        --element_size;
    }
}


static void *BSearch(char *arr, size_t start, size_t end, size_t element_size,
    compar_t compar, const void *to_seek)
{
    size_t middle = (start + end )/ 2;
    int res_compar = compar(to_seek, arr + (middle * element_size));

    if (0 == res_compar)
    {
        return (arr + (middle * element_size));
    }

    if (start == end)
    {
        return NULL;
    }
    else
    {
        if (0 > res_compar)
        {
            return BSearch(arr, start, middle, element_size, compar, to_seek);
        }
        else
        {
            return BSearch(arr, middle, end, element_size, compar, to_seek);
        }
    }
}
