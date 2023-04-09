#include <stdlib.h>
#include <string.h>
#include "fsq.h"

struct fsq_s
{
	size_t enq_index;
	size_t deq_index;
	size_t capacity;
	int buffer[1];
};

fsq_t *FSQCreate(size_t nmemb)
{
	fsq_t *new_fsq = malloc(sizeof(fsq_t) + nmemb * sizeof(int));


	if (NULL != new_fsq)
	{
		memset(new_fsq, 0, sizeof(fsq_t) + nmemb * sizeof(int));
		new_fsq->enq_index = 0;
		new_fsq->deq_index = 0;
		new_fsq->capacity = nmemb;
	}

	return new_fsq;
}

void FSQDestroy(fsq_t *fsq)
{
	free(fsq);

	fsq = NULL;
}

void FSQEnqueue(fsq_t *fsq, int val)
{

	fsq->buffer[fsq->enq_index] = val;

	++fsq->enq_index;

	fsq->enq_index %= fsq->capacity;
}

int FSQDequeue(fsq_t *fsq)
{
	int first_in_q = fsq->buffer[fsq->deq_index];

	++fsq->deq_index;

	fsq->deq_index %= fsq->capacity;

	return first_in_q;
}
