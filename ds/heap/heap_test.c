/*==============================================================================
Data Structures - Heap
Tests
Dekel Sror
Review - Shon Weinberg
RC 1
==============================================================================*/
#include <stdio.h>  /* printf */
#include <stdlib.h> /* malloc, free, rand, srand */
#include <unistd.h> /* getpid */

#include "heap.h" /* heap_t, heap API */

#define TEST_SIZE (50000lu)

typedef enum cmp_lut_e { MAX_HEAP, MIN_HEAP } cmp_lut_t;

static void TestIsEmpty(heap_t *heap, int exp_res, size_t *test_count);
static void TestCount(heap_t *heap, size_t exp_res, size_t *test_count);
static void TestInsertCount(
	heap_t *heap,
	int *buffer,
	size_t how_big,
	size_t *test_count);

static void TheBigRemove(size_t how_big, cmp_lut_t heap_func, size_t *test_count);
static void TheBigPop(size_t how_big, cmp_lut_t heap_func, size_t *test_count);
static int IsGoodHeap(int current, int last, cmp_lut_t heap_func);

/* argument functions */
static int MaxHeap(const void *data, const void *heap_data);
static int MinHeap(const void *data, const void *heap_data);
static int RemoveByValue(const void *heap_data, void *arg);

int main(void)
{
	size_t successes = 0;

	TheBigPop(TEST_SIZE, MAX_HEAP, &successes);
	printf("pop tests passed with MaxHeap %lu\n", successes);
	successes = 0;

	TheBigPop(TEST_SIZE, MIN_HEAP, &successes);
	printf("pop tests passed with MinHeap %lu\n", successes);
	successes = 0;

	TheBigRemove(TEST_SIZE, MAX_HEAP, &successes);
	printf("remove tests passed with MaxHeap %lu\n", successes);
	successes = 0;

	TheBigRemove(TEST_SIZE, MIN_HEAP, &successes);
	printf("remove tests passed with MinHeap %lu\n", successes);

	return 0;
}

static void TheBigPop(size_t how_big, cmp_lut_t heap_func, size_t *test_count)
{
	size_t i = 0;
	heap_cmp_t little_lut[2] = { MaxHeap, MinHeap };
	heap_t *test = HeapCreate(little_lut[heap_func]);
	int *buffer = malloc(sizeof(int) * how_big);
	int *putter = buffer;
	int last_peek = ((heap_func == MAX_HEAP) ? RAND_MAX : -1);

	srand(getpid());

	TestInsertCount(test, buffer, how_big, test_count);

	for (i = 0; i < how_big; ++i, ++putter)
	{
		int peek = *(int *)HeapPeek(test);

		if (!IsGoodHeap(peek, last_peek, heap_func))
		{
			printf("failed to keep heap heaped [func %d]. peeked %d after popping %d\n"
					, heap_func, peek, last_peek);
		}
		else
		{
			++*test_count;
		}

		last_peek = peek;
		HeapPop(test);
	}

	HeapDestroy(test);
	test = NULL;
	free(buffer);
	buffer = NULL;
}

static void TheBigRemove(size_t how_big, cmp_lut_t heap_func, size_t *test_count)
{
	size_t i = 0;
	heap_cmp_t little_lut[2] = { MaxHeap, MinHeap };
	heap_t *test = HeapCreate(little_lut[heap_func]);
	int *buffer = malloc(sizeof(int) * how_big);
	int *putter = buffer;
	int last_peek = ((heap_func == MAX_HEAP) ? RAND_MAX : -1);


	TestInsertCount(test, buffer, how_big, test_count);

	for (i = 0; i < how_big; ++i, ++putter)
	{
		int peek = *(int *)HeapPeek(test);
		void *rm_res = NULL;

		TestCount(test, how_big - i, test_count);
		rm_res = HeapRemove(test, RemoveByValue , putter);

		if (NULL == rm_res)
		{
			printf("[%lu] failed to locate and remove %d\n", i, *putter);
		}
		else
		{
			++*test_count;
		}

		if (!IsGoodHeap(peek, last_peek, heap_func))
		{
			printf("failed to keep heap heaped [func %d]. peeked %d after removing %d\n"
					, heap_func, peek, last_peek);
		}
		else
		{
			++*test_count;
		}

		last_peek = peek;
	}

	TestIsEmpty(test, 1, test_count);

	HeapDestroy(test);
	test = NULL;
	free(buffer);
	buffer = NULL;
}

static int IsGoodHeap(int current, int last, cmp_lut_t heap_func)
{
	if (
		((heap_func == MAX_HEAP) && (current > last))
		  || ((heap_func == MIN_HEAP) && (current < last))
		)
	{
		printf("no good heap_func %d current %d last %d\n", heap_func, current, last);
		return 0;
	}

	return 1;
}

static void TestInsertCount(
	heap_t *heap,
	int *buffer,
	size_t how_big,
	size_t *test_count)
{
	int *putter = buffer;
	size_t i = 0;

	TestIsEmpty(heap, 1, test_count);

	for (i = 0; i < how_big; ++i, ++putter)
	{
		int err = 0;

		*putter = rand() % 0x05050505;
		TestCount(heap, i, test_count);
		err = HeapPush(heap, putter);

		if (err)
		{
			printf("error while inserting [%d]\n", err);
		}
		else
		{
			++*test_count;
		}
	}
	TestIsEmpty(heap, 0, test_count);
}

static void TestIsEmpty(heap_t *heap, int exp_res, size_t *test_count)
{
	int res = HeapIsEmpty(heap);

	if (exp_res != res)
	{
		printf("HeapIsEmpty failed, exp_res %d, res %d\n"
				, exp_res, res);
	}
	else
	{
		++*test_count;
	}
}

static void TestCount(heap_t *heap, size_t exp_res, size_t *test_count)
{
	size_t res = HeapCount(heap);

	if (exp_res != res)
	{
		printf("failed to count. had %lu, exp_res %lu\n"
			, res, exp_res);
	}
	else
	{
		++*test_count;
	}
}

/* argument functions */
static int RemoveByValue(const void *heap_data, void *arg)
{
	if (*(int *)heap_data == *(int *)arg)
	{
		return 1;
	}

	return 0;
}

static int MaxHeap(const void *data, const void *heap_data)
{
	return *(int *)data > *(int *)heap_data;
}

static int MinHeap(const void *data, const void *heap_data)
{
	return *(int *)data < *(int *)heap_data;
}
