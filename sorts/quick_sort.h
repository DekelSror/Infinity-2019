#ifndef DEKEL_QSORT_YAKOV_H
#define DEKEL_QSORT_YAKOV_H


#include <stddef.h> /* size_t */

typedef int (*compar_t) (const void *, const void *);

void QuickSort	  (void *arr, size_t nmemb, size_t element_size,
                   compar_t compar
                  );
void *BinarySearch(void *arr, size_t nmemb, size_t element_size,
                    compar_t compar, const void *to_seek);

#endif /* DEKEL_QSORT_YAKOV_H */
