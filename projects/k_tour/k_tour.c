/*==============================================================================
Knight's Tour
Module
Dekel Sror
Review - Yakov Gorochovski
RC 1 - implementation depends on gnu-native qsort_r to sort tours
==============================================================================*/
#ifndef _GNU_SOURCE /* qsort_r */
#define _GNU_SOURCE
#endif /* _GNU_SOURCE */

#include <stdlib.h> /* qsort_r */
#include <stdio.h>  /* printf  */
#include <time.h> 	/* clock_t, clock */
#include <unistd.h>
#include <string.h>

#include "istack.h" /* istack_t, stack API */
#include "k_tour.h"

 /* colors for clearer output */
#define RED_BOLD "\033[1;31m"
#define GRN_BOLD "\033[1;32m"
#define RESET    "\033[0m"

#define NUM_SQUARES (64)
#define NUM_TOURS (8)
/* to run both Warsnsdorff heuristic and brute force approach */
#define NUM_ALGO (2)
#define TIMEOUT_INTERVAL (600 * CLOCKS_PER_SEC)

typedef enum k_status_e { NOT_FOUND, FOUND, TIMEOUT } k_status_t;

typedef struct map_index_s
{
	short tours[NUM_TOURS];
	short tour_count;
} map_index_t;

#define MARK_POS(brd, pos) (brd |= (1lu << pos))
#define IS_MARKED(brd, pos) (( brd & (1lu << pos) ) >> pos)
#define IS_BOARD_FULL(brd) (0xffffffffffffffff == brd)
#define IS_ON_BOARD(row, col) ((0 <= col && 7 >= col) && (0 <= row && 7 >= row))

/* sorting method for position tours */
static int TourCmp(const void *t1, const void *t2, void *arg);
static void MapInit(map_index_t *map, size_t algo);
static void ShowPath(istack_t *stack);
static k_status_t KTour
(
	size_t board,
	short pos,
	const map_index_t *tour_map,
	istack_t *path_stack,
	clock_t timer
);

void KnightsTour(void)
{
	short pos = 0;
	istack_t *path_stack = IntStackCreate(NUM_SQUARES);
	static map_index_t tour_map[NUM_SQUARES] = { { {0}, 0 } };
	size_t i_algorithm = 0;


	for (i_algorithm = 0; i_algorithm < NUM_ALGO; ++i_algorithm)
	{
		memset(tour_map, 0, sizeof(map_index_t) * NUM_SQUARES);
		MapInit(tour_map, i_algorithm);

		for (pos = 0; pos < NUM_SQUARES; ++pos)
		{
			size_t board = 0;
			clock_t timer = clock();
			k_status_t sqr_result = KTour(board, pos, tour_map, path_stack, timer);
			double runtime = (double)(clock() - timer) / (double)CLOCKS_PER_SEC;

			if (FOUND == sqr_result)
			{
				printf(GRN_BOLD);
				printf("found for %d in %f seconds\n", pos, runtime);
				printf(RESET);
				ShowPath(path_stack);
				printf("\n");
			}
			else
			{
				printf(RED_BOLD);
				printf("\nstatus for %d: %d , seconds %f\n"
						, pos, sqr_result, runtime);
				printf(RESET);
				printf("\n");
			}
		}
	}

	IntStackDestroy(path_stack);
}

/* recursively searches board for a full tour */
static k_status_t KTour
(
	size_t board,
	short pos,
	const map_index_t *tour_map,
	istack_t *path_stack,
	clock_t timer)
{
	k_status_t status = NOT_FOUND;
	short i_tour = 0;

	if ((clock() - timer) > TIMEOUT_INTERVAL)
	{
		return TIMEOUT;
	}

	if (IS_BOARD_FULL(board))
	{
		return FOUND;
	}

	if (IS_MARKED(board, pos))
	{
		return NOT_FOUND;
	}

	MARK_POS(board, pos);

	for (i_tour = 0; i_tour < NUM_TOURS; ++i_tour)
	{
		if ((NOT_FOUND == status) && (-1 != tour_map[pos].tours[i_tour]))
		{
			status = KTour(board, tour_map[pos].tours[i_tour],
							tour_map, path_stack, timer);
		}
	}

	if (FOUND == status)
	{
		IntStackPush(path_stack, pos);

		return FOUND;
	}

	return status;
}

static void MapInit(map_index_t *map, size_t algo)
{
	short i_sqr = 0;
	short i_tour = 0;

	for (i_sqr = 0; i_sqr < NUM_SQUARES; ++i_sqr)
	{
		map[i_sqr].tour_count = 0;

		for (i_tour = 0; i_tour < NUM_TOURS; ++i_tour)
		{
			map[i_sqr].tours[i_tour] = -1;
		}
	}

	for (i_sqr = 0; i_sqr < NUM_SQUARES; ++i_sqr)
	{
		short col = i_sqr % 8;
		short row = i_sqr / 8;
		i_tour = 0;

		if (IS_ON_BOARD(col + 2, row + 1))
		{
			map[i_sqr].tours[i_tour] = col + 2 + (row + 1) * 8;
			++map[i_sqr].tour_count;
		}

		++i_tour;

		if (IS_ON_BOARD(col + 2, row - 1))
		{
			map[i_sqr].tours[i_tour] = col + 2 + (row - 1) * 8;
			++map[i_sqr].tour_count;
		}

		++i_tour;

		if (IS_ON_BOARD(col - 2, row + 1))
		{
			map[i_sqr].tours[i_tour] = col - 2 + (row + 1) * 8;
			++map[i_sqr].tour_count;
		}

		++i_tour;

		if (IS_ON_BOARD(col - 2, row - 1))
		{
			map[i_sqr].tours[i_tour] = col - 2 + (row - 1) * 8;
			++map[i_sqr].tour_count;
		}

		++i_tour;

		if (IS_ON_BOARD(col + 1, row + 2))
		{
			map[i_sqr].tours[i_tour] = col + 1 + (row + 2) * 8;
			++map[i_sqr].tour_count;
		}

		++i_tour;

		if (IS_ON_BOARD(col + 1, row - 2))
		{
			map[i_sqr].tours[i_tour] = col + 1 + (row - 2) * 8;
			++map[i_sqr].tour_count;
		}

		++i_tour;

		if (IS_ON_BOARD(col - 1, row + 2))
		{
			map[i_sqr].tours[i_tour] = col - 1 + (row + 2) * 8;
			++map[i_sqr].tour_count;
		}

		++i_tour;

		if (IS_ON_BOARD(col - 1, row - 2))
		{
			map[i_sqr].tours[i_tour] = col - 1 + (row - 2) * 8;
			++map[i_sqr].tour_count;
		}
	}

	if (0 == algo)
	{
		for (i_sqr = 0; i_sqr < NUM_SQUARES; ++i_sqr)
		{
			qsort_r(map[i_sqr].tours, NUM_TOURS, sizeof(short), TourCmp, map);
		}
	}

	printf("Knight Tour Map\n\n");

	for (i_sqr = 0; i_sqr < NUM_SQUARES; ++i_sqr)
	{
		printf("tours for %d -\n", i_sqr);
		{
			printf("\t");
			for (i_tour = 0; i_tour < NUM_TOURS; ++i_tour)
			{
				printf("%d, ", map[i_sqr].tours[i_tour]);
			}
			printf("\n");
		}
	}
	printf("\n\n\n");
}

/* passed to qsort. Sorts positions with less tours first, invalid last */
static int TourCmp(const void *t1, const void *t2, void *arg)
{
	map_index_t *map = (map_index_t *)arg;

	if (-1 == *(short *)t1)
	{
		return 1;
	}

	if (-1 == *(short *)t2)
	{
		return -1;
	}

	return map[*(short *)t1].tour_count - map[*(short *)t2].tour_count;
}

/* Empties path_stack to either or both stdout and debug.txt  */
static void ShowPath(istack_t *stack)
{
	short index = 0;

	printf("\npath for position %d:\n\n", IntStackPeek(stack));

	while (0 < IntStackSize(stack))
	{
		printf("%d:%d, ", index, IntStackPeek(stack));

		IntStackPop(stack);
		++index;
	}

	printf("\n\n");
}
