

#ifndef SORTS_HHH_
#define SORTS_HHH_

#include <stddef.h>

void InsertionSort(int *arr, size_t len);
void SelectionSort(int *arr, size_t len);
void BubbleSort   (int *arr, size_t len);
void MergeSort	  (int *arr, size_t len);
void CountingSort (int *arr, size_t len, size_t range);
void RadixSort    (int *arr, size_t len, size_t radix);
void HeapSort	  (int *arr, size_t len);


#endif /* SORTS_HHH_ */
