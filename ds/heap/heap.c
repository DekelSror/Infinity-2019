/*==============================================================================
Data Structures - Heap
Module
Dekel Sror
Review - Shon Weinberg
RC 1
==============================================================================*/
#include <stdlib.h> /* malloc, free 		*/
#include <assert.h> /* assert				*/

#include "vector.h" /* vector_t, vector API */
#include "heap.h"

#define WORD_SIZE (sizeof(void *))

#define I_FIRST (1)
#define HEAP_INITIAL_SIZE (0x100)

#define HEAP_GET(heap, index) ((void **)VectorGet(heap->vector, index))
#define HEAP_LAST(heap)	  (VectorSize(heap->vector) - 1)
#define LEFT_CHILD(index) (index * 2)
#define RIGHT_CHLID(index) (LEFT_CHILD(index) + 1)

static void SwapData(void **data_1, void **data_2);
static void HeapifyDown(heap_t *heap, size_t index);
static void HeapifyUp(heap_t *heap, size_t index);

struct heap_s
{
	heap_cmp_t is_above;
	vector_t *vector;
};

heap_t *HeapCreate(heap_cmp_t IsPrior)
{
	void *magic_num = (void *)0xdab1d00f;
	heap_t *new_heap = malloc(sizeof(heap_t));

	if (NULL == new_heap)
	{
		return NULL;
	}

	new_heap->is_above = IsPrior;
	new_heap->vector = VectorCreate(WORD_SIZE, HEAP_INITIAL_SIZE);

	if (NULL == new_heap->vector)
	{
		free(new_heap);
		new_heap = NULL;

		return NULL;
	}

	/* dummy member to simplify child / parent formulas		  */
	/* this must work since create with 11 elements succeeded */
	VectorPush(new_heap->vector, &magic_num);

	return new_heap;
}

void HeapDestroy(heap_t *heap)
{
	assert(heap);

	VectorDestroy(heap->vector);

	free(heap);

	heap = NULL;
}

int HeapPush(heap_t *heap, void *data)
{
	int push_err = 0;

	assert(heap);

	push_err = VectorPush(heap->vector, &data);

	if (push_err)
	{
		return push_err;
	}

	HeapifyUp(heap, HEAP_LAST(heap));

	return 0;
}

void HeapPop(heap_t *heap)
{
	SwapData(HEAP_GET(heap, I_FIRST), HEAP_GET(heap, HEAP_LAST(heap)));

	VectorPop(heap->vector);

	HeapifyDown(heap, I_FIRST);
}

void *HeapPeek(const heap_t *heap)
{
	return *HEAP_GET(heap, I_FIRST);
}

size_t HeapCount(const heap_t *heap)
{
	return HEAP_LAST(heap);
}

int HeapIsEmpty(const heap_t *heap)
{
	return (0 == HEAP_LAST(heap));
}

void *HeapRemove(heap_t *heap, heap_cond_t condition_func, void *arg)
{
	size_t i = 0;
	size_t i_last = HEAP_LAST(heap);
	void **last_member = HEAP_GET(heap, i_last);

	/* from first user index to last, inclusive */
	for (i = I_FIRST; i <= i_last; ++i)
	{
		void **to_rm = HEAP_GET(heap, i);

		if (condition_func(*to_rm, arg))
		{
			SwapData(to_rm, last_member);

			VectorPop(heap->vector);

			HeapifyUp(heap, i);
			HeapifyDown(heap, i);

			return *last_member;
		}
	}

	return NULL;
}

/* end of heap API */
static void HeapifyUp(heap_t *heap, size_t index)
{
	if ((index / 2) < I_FIRST)
	{
		return;
	}
	else
	{
		size_t i_parent = index / 2;
		void **parent_data = HEAP_GET(heap, i_parent);
		void **node_data = HEAP_GET(heap, index);

		if (heap->is_above(*node_data, *parent_data))
		{
			SwapData(HEAP_GET(heap, index), HEAP_GET(heap, i_parent));
			HeapifyUp(heap, i_parent);
		}
	}
}

static void HeapifyDown(heap_t *heap, size_t index)
{
	if (LEFT_CHILD(index) > HEAP_LAST(heap))
	{
		return;
	}
	else
	{
		size_t i_max_kid = LEFT_CHILD(index);

		if ((RIGHT_CHLID(index)) <= (HEAP_LAST(heap)))
		{
			if (heap->is_above(*HEAP_GET(heap, RIGHT_CHLID(index)),
							   *HEAP_GET(heap, LEFT_CHILD(index))))
			{
				++i_max_kid;
			}
		}

		if (heap->is_above(*HEAP_GET(heap, i_max_kid),
						   *HEAP_GET(heap, index)))
		{
			SwapData(HEAP_GET(heap, i_max_kid), HEAP_GET(heap, index));
			HeapifyDown(heap, i_max_kid);
		}
	}
}

static void SwapData(void **data_1, void **data_2)
{
	void *swap = *data_1;

	*data_1 = *data_2;
	*data_2 = swap;
}
