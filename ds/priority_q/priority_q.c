/*==============================================================================
Data Structures - Priotiy Queue
Module
Dekel Sror
Review: Tal Shabtai
OL66
Version 1
==============================================================================*/
#include <stdlib.h> /* malloc, free, NULL */
#include <assert.h> /* assert */
#include <stdio.h> /**/

#include <sorted_ll.h> /* sliter_t sortedlist_t, sorted_ll API */

#include "priority_q.h"

struct pq_s
{
    sortedlist_t *queue;
    is_prior_t priority_method;
};

void PQPrint(pq_t *test)
{
    sliter_t printer = SortedListBegin(test->queue);

    printf("\n- - - - - - - - - - - - - - - - -\n");

    while (!SortedListIsSameIter(printer, SortedListEnd(test->queue)))
    {
        printf("%d, ", *(int *)SortedListGetData(printer));
        printer = SortedListNext(printer);
    }

    printf("\n- - - - - - - - - - - - - - - - -\n");
}

pq_t *PriorityQCreate(is_prior_t is_prior)
{
    pq_t *new_pq = (pq_t *)malloc(sizeof(pq_t));

    if (NULL == new_pq)
    {
        return NULL;
    }

    new_pq->queue = SortedListCreate(is_prior);

    new_pq->priority_method = is_prior;

    return new_pq;
}

void PriorityQDestroy(pq_t *pq)
{
    assert(pq);

    SortedListDestroy(pq->queue);

    free(pq);

    pq = NULL;
}

int PriorityQEnqueue(pq_t *pq, void *data)
{
    sliter_t iter = SortedListInsert(pq->queue, data);

    return (SortedListGetData(iter) != NULL);
}

void PriorityQDequeue(pq_t *pq)
{
    assert(pq);

    SortedListPopFront(pq->queue);
}

size_t PriorityQSize(const pq_t *pq)
{
    assert(pq);

    return SortedListCount(pq->queue);
}

int PriorityQIsEmpty(const pq_t *pq)
{
    assert(pq);

    return SortedListIsEmpty(pq->queue);
}

void *PriorityQPeek(const pq_t *pq)
{
    assert(pq);

    return SortedListGetData(SortedListBegin(pq->queue));
}

void PriorityQClear(pq_t *pq)
{
    sliter_t eraser = { 0 };
    sliter_t next_iter = { 0 };

    assert(pq);

    eraser = SortedListBegin(pq->queue);

    while (!SortedListIsSameIter(eraser, SortedListEnd(pq->queue)))
    {
        next_iter = SortedListNext(eraser);
        SortedListErase(eraser);
        eraser = next_iter;
    }
}

void PriorityQErase(pq_t *pq, criteria_func_t criteria_func, void *arg)
{
    sliter_t iter = { 0 };

    assert(pq);
    assert(criteria_func);

    iter = SortedListBegin(pq->queue);

    while (!SortedListIsSameIter(iter, SortedListEnd(pq->queue)))
    {
        if (criteria_func(SortedListGetData(iter), arg))
        {
            iter = SortedListErase(iter);
        }
        else
        {
            iter = SortedListNext(iter);
        }
    }
}
