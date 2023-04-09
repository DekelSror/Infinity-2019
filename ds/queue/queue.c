/*==============================================================================
Data Structures - Queue based on linked_list
Module
Dekel Sror
Review: Tzvi Cubac
Version 4
==============================================================================*/

#include <stdlib.h> /* malloc, free, NULL */
#include <assert.h> /* assert             */
#include <stdio.h>  /* printf (QPrint)    */

#include "linked_list.h" /* entire module */
#include "queue.h"

/* queue type definition */
struct queue_t
{
    node_t *first;
    node_t *last;
};

queue_t *QCreate(void)
{
    queue_t *new_q = (queue_t *)malloc(sizeof(queue_t));

    if (NULL == new_q)
    {
        return NULL;
    }

    new_q->first = ListCreateNode(NULL, NULL);

    if (NULL == new_q->first)
    {
        free(new_q);

        return NULL;
    }

    new_q->last = new_q->first;

    return new_q;
}

void QDestroy(queue_t *queue)
{
    assert(queue);

    ListFreeAll(queue->first);

    free(queue);

    queue = NULL;
}

int QEnqueue(queue_t *queue, void *data)
{
    node_t *new_node = NULL;

    assert(queue);
    assert(data);

    new_node = ListCreateNode(data, NULL);

    if (NULL == new_node)
    {
        return 1;
    }

/* new_node is added to back of queue */
    queue->last = ListInsert(new_node, queue->last)->next;

    return 0;
}

void QDequeue(queue_t *queue)
{
    node_t *keeper = NULL;

    assert(queue);

    keeper = queue->first->next;

    free(queue->first);

    queue->first = keeper;
}

size_t QSize(const queue_t *queue)
{
    assert(queue);

/* actual size without dummy link */
    return ListCount(queue->first) - 1;
}

int QIsEmpty(const queue_t *queue)
{
    assert(queue);

    return 0 == QSize(queue);

}

void *QPeek(const queue_t *queue)
{
    assert(queue);

    return queue->first->data;
}

void QAppend(queue_t *dest, queue_t *src)
{
    node_t *src_dummy = NULL;

    assert(dest);
    assert(src);

    src_dummy = src->first;

/* connect ends, convert dest dummy to real node */
    dest->last->data = src->first->data;
    dest->last->next = src->first->next;

/* create a new dummy link for src */
    src_dummy->data = NULL;
    src_dummy->next = NULL;

/* rewind to end of joined queue */
    dest->last = src->last;

/* assign new dummy to src at both ends */
    src->first = src->last = src_dummy;
}

/* utility - include stdio.h to use */
void QPrint(const queue_t *q)
{
    printf("first->");
    ListPrint(q->first);
    printf("<-last\n\n");
}
