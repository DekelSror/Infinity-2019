/* build queue around two stacks of integers */


#ifndef QUEUE_FROM_2_STACKS
#define QUEUE_FROM_2_STACKS

#include <istack.h>

typedef struct sq_s sq_t;

sq_t *SQCreate(size_t num_of_elems);

void SQDestroy(sq_t*q);

void SQEnqueue(sq_t *q, int element);

void SQDequeue(sq_t *q);

int SQPeek(sq_t *q);


#endif /* QUEUE_FROM_2_STACKS */
