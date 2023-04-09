/*==============================================================================
Data Structures - Heap
Version 1.0
==============================================================================*/

#ifndef ILRD_HEAP_H
#define ILRD_HEAP_H

#include <stddef.h>

typedef struct heap_s heap_t;

/*
	returns 1 if data is above heap data
*/
typedef int(*heap_cmp_t)(const void *data, const void *heap_data);
typedef int(*heap_cond_t)(const void *heap_data, void *arg);

/*
Crates a new heap

args -
is_prior -

returns handle to new heap
*/
heap_t *HeapCreate(heap_cmp_t IsPrior);

/*
Free all memory assiciated with heap

args -
heap - a hea_t handle
*/
void HeapDestroy(heap_t *heap);

/*
adds data to heap

args -
heap - heap_t handle
data - new member data

returns 0 on success
*/
int HeapPush(heap_t *heap, void *data);

/*
pops top of heap

args -
heap - a heap_t handle;
*/
void HeapPop(heap_t *heap);

/*
get data of top member of heap

args -
heap - a heap_t handle

returns data stored in top of heap
*/
void *HeapPeek(const heap_t *heap);

/*
counts members in heap

args -
heap - a heap_t handle

returns member count
*/
size_t HeapCount(const heap_t*);

/*
checks if heap has no members

args -
heap - a heap_t handle
*/
int HeapIsEmpty(const heap_t *heap);

/*
removes first members in heap using condition_func

args -
heap - a heap_t handle
condition_func - conditional function. must confirm to rmv_func
arg - optional additional args of condition_func

returns - reference to removed data, NULL if nothing was removed
*/
void *HeapRemove(heap_t *heap, heap_cond_t condition_func, void *arg);

#endif /* ILRD_HEAP_H */
