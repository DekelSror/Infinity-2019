#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>

#include "avl.h"
#include "useful.h"


#define TREE_SIZE (2540lu)

typedef enum scheme_e { RANDOM, SEQUENTIAL } scheme_t;

/* unit tests */
/* one test */
static void TestCount(avl_t *tree, size_t exp_res, size_t *successes);
static void TestFindEverything(avl_t *tree, int *buffer, size_t num_nodes,
	size_t *successes);
/* TREE_SIZE + 1 */
static void TestForEach(avl_t *tree, avl_op_t op, size_t num_nodes, size_t *successes);
static void TestRemove(avl_t *tree, const int *buffer, size_t num_nodes,
						size_t num_del, size_t *successes);


static void CheckHeight(avl_t *tree, size_t num_nodes, size_t *successes);

/* argument functions */
static int SmallToLeft(const void *num1, const void *num2);
static int CountUs(void *data, void *arg);

/* utility */
static avl_t *GenerateTree
(
	int *buffer, size_t num_nodes, scheme_t insert_scheme, size_t *successes
);

int main(void)
{
	int data_buff[TREE_SIZE] = { 0 };
	size_t successes = 0;
	avl_t *test = GenerateTree(data_buff, TREE_SIZE, RANDOM, &successes);

	TestCount(test, TREE_SIZE, &successes);

	TestFindEverything(test, data_buff, TREE_SIZE, &successes);

	TestForEach(test, CountUs, TREE_SIZE, &successes);

	TestRemove(test, data_buff, TREE_SIZE, TREE_SIZE / 2, &successes);

	printf(PRP_BOLD);
	printf("first part tests passed: %lu\n", successes);
	printf(RESET);
	printf("second part\n");
	TestFindEverything(test, data_buff + TREE_SIZE / 2, TREE_SIZE / 2, &successes);

	TestForEach(test, CountUs, TREE_SIZE / 2, &successes);

	TestRemove(test, data_buff + TREE_SIZE / 2, AVLCount(test), TREE_SIZE / 2, &successes);

	AVLDestroy(test);

	printf(PRP_BOLD);
	printf("second part tests passed: %lu\n", successes);
	printf(RESET);

	return 0;
}

static int CountUs(void *data, void *arg)
{
	UNUSED(data);

	++*(size_t *)arg;

	return 0;
}

static void CheckHeight(avl_t *tree, size_t num_nodes, size_t *successes)
{
	size_t actual_height = AVLHeight(tree);
	size_t min_height = log10( num_nodes + 1) / log10(2);
    size_t max_height = (1.44 * log10(num_nodes + 2) / log10(2) - 0.328);

	if (actual_height <= max_height &&
			actual_height >= min_height)
	{
		++*successes;
	}
}

static void TestRemove(avl_t *tree, const int *buffer, size_t num_nodes,
						size_t num_del, size_t *successes)
{

	for (; 0 < num_del; --num_del, --num_nodes, ++buffer)
	{
		size_t api_count = AVLCount(tree);

		CheckHeight(tree, num_nodes, successes);

		if (num_nodes != api_count)
		{
			printf("removal isn't right. count is %lu, exp_res %lu\n",
					api_count, num_nodes);
		}
		else
		{
			++*successes;
		}

		AVLRemove(tree, buffer);
	}
}

static void TestForEach(avl_t *tree, avl_op_t op, size_t num_nodes, size_t *successes)
{
	size_t count_arg = 0;
	int res = AVLForEach(tree, op, &count_arg);

	if (0 != res)
	{
		printf("failed to for each entirely!\n");
	}
	else
	{
		++*successes;
	}

	if (num_nodes != count_arg)
	{
		printf("ForEach failed to count, had %lu, exp_res %lu\n"
			, count_arg, num_nodes);
	}
	else
	{
		++*successes;
	}
}

static void TestCount(avl_t *tree, size_t exp_res, size_t *successes)
{
	size_t res = AVLCount(tree);

	if (res != exp_res)
	{
		printf("TestCount failed, had %lu, exp_res %lu\n", res, exp_res);
	}
	else
	{
		++*successes;
	}
}

static void TestFindEverything(avl_t *tree, int *buffer, size_t num_nodes,
	size_t *successes)
{
	int *buff_end = buffer + num_nodes;
	int should_not_be_found = -3; /* rand() values are non-negative */
	size_t when = 0;

	while (buffer < buff_end)
	{
		if (buffer == AVLFind(tree, buffer))
		{
			++*successes;
		}
		else
		{
			printf("TestFind failed to find buffer[%lu], %d\n", when, *buffer);
		}

		++when;
		++buffer;
	}

	if (NULL == AVLFind(tree, &should_not_be_found))
	{
		++*successes;
	}
	else
	{
		printf("TestFind to NOT find %d\n", should_not_be_found);
	}
}

static avl_t *GenerateTree
(
	int *buffer,
	size_t num_nodes,
	scheme_t insert_scheme,
	size_t *successes
)
{
	avl_t *tree = AVLCreate(SmallToLeft);
	int *putter = buffer;
	int *end = buffer + num_nodes;
	size_t tree_count = 0;

	srand(5051);

	{
		while (putter < end)
		{
			if (RANDOM == insert_scheme)
			{
				*putter = rand();
			}
			else
			{
				*putter = tree_count;
			}

			AVLInsert(tree, putter);

			++tree_count;
			++putter;

			TestCount(tree, tree_count, successes);
		}
	}

	return tree;
}

static int SmallToLeft(const void *num1, const void *num2)
{
	return *(int *)num1 - *(int *)num2;
}
