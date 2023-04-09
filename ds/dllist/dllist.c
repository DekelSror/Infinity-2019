/*==============================================================================
Data Structures - Doubly Linked List with iterators
Module
Dekel Sror
Review: Moti Zamir
OL66
Version 2
==============================================================================*/
#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert       */

#include "dllist.h"

typedef struct dnode_s dnode_t;

#define ITER_TO_NODE(x) ((dnode_t *)x.info)

struct dnode_s
{
    void *data;
    dnode_t *next;
    dnode_t *prev;
};

struct dlist_s
{
    dnode_t begin;
    dnode_t end;
};

diter_t DLBegin(const dlist_t *list)
{
    diter_t res = { 0 };

    assert(list);

    res.info = list->begin.next;

    return res;
}

diter_t DLEnd(const dlist_t *list)
{
    diter_t res = { 0 };

    assert(list);

    res.info = (dnode_t *)&list->end;

    return res;
}

diter_t DLNext(diter_t iter)
{
    iter.info = (ITER_TO_NODE(iter))->next;

    return iter;
}

diter_t DLPrev(diter_t iter)
{
    iter.info = (ITER_TO_NODE(iter))->prev;

    return iter;
}

int DLIsSameIter(const diter_t iter1, const diter_t iter2)
{
    return (iter1.info == iter2.info);
}

void *DLGetData(diter_t iter)
{
    return (ITER_TO_NODE(iter))->data;
}

dlist_t *DLCreate(void)
{
    dlist_t *new_dl = (dlist_t *)malloc(sizeof(dlist_t));

    if (NULL == new_dl)
    {
        return NULL;
    }

    new_dl->begin.data = NULL;
    new_dl->end.data = NULL;

    new_dl->begin.prev = NULL;
    new_dl->end.next = NULL;

    new_dl->begin.next = &new_dl->end;
    new_dl->end.prev = &new_dl->begin;

    return new_dl;
}

void DLDestroy(dlist_t *list)
{
    diter_t eraser = { 0 };
    diter_t next_iter = { 0 };

    assert(list);

    eraser = DLBegin(list);

    while (!DLIsSameIter(eraser, DLEnd(list)))
    {
        next_iter = DLNext(eraser);
        free((dnode_t *)eraser.info);
        eraser = next_iter;
    }

    free(list);
    list = NULL;
}

size_t DLCount(const dlist_t *list)
{
    diter_t dit = { 0 };
    size_t count = 0;

    assert(list);

    dit = DLBegin(list);

    while (!DLIsSameIter(dit, DLEnd(list)))
    {
        ++count;
        dit = DLNext(dit);
    }

    return count;
}

int DLIsEmpty(const dlist_t *list)
{
    assert(list);

    return DLIsSameIter(DLBegin(list), DLEnd(list));
}

/*  this is the only function that allocates for dnodes */
diter_t DLInsert(dlist_t *list, diter_t iter, void *data)
{
    dnode_t *new_node = NULL;
    dnode_t *dnode_post = ITER_TO_NODE(iter);

    assert(list);
    assert(data);

    new_node = (dnode_t *)malloc(sizeof(dnode_t));

    if (NULL == new_node)
    {
        return DLEnd(list);
    }

    new_node->data = data;
    new_node->next = dnode_post;
    new_node->prev = dnode_post->prev;

/* link existing nodes to new_node on both ends */
    dnode_post->prev->next = new_node;
    dnode_post->prev = new_node;

    return DLPrev(iter);
}


diter_t DLInsertAfter(dlist_t *list, diter_t iter, void *data)
{
    assert(list);

    return DLInsert(list, DLNext(iter), data);
}

void DLErase(diter_t iter)
{
    dnode_t *dnode_ptr = ITER_TO_NODE(iter);

    dnode_ptr->prev->next = dnode_ptr->next;
    dnode_ptr->next->prev = dnode_ptr->prev;

    free(dnode_ptr);
    dnode_ptr = NULL;
}

diter_t DLPushFront(dlist_t *list, void *data)
{
    assert(list);
    assert(data);

    return DLInsert(list, DLBegin(list), data);
}

diter_t DLPushBack(dlist_t *list, void *data)
{
    assert(list);
    assert(data);

    return DLInsert(list, DLEnd(list), data);
}

void DLPopFront(dlist_t *list)
{
    assert(list);

    DLErase(DLBegin(list));
}

void DLPopBack(dlist_t *list)
{
    assert(list);

    DLErase(DLPrev(DLEnd(list)));
}

int DLForEach(diter_t from, diter_t to
            , int (*operation_func)(void *data, void *argument)
            , void *argument)
{
    int op_status = 0;

    assert(argument);
    assert(operation_func);

    while ((0 == op_status) && (!DLIsSameIter(from, to)))
    {
        op_status = operation_func(DLGetData(from), argument);
        from = DLNext(from);
    }

    return op_status;
}

/* assuming a boolean cmp_func */
diter_t DLFind(
          diter_t from
        , diter_t to
        , int(*cmp_func)(const void *data, const void *to_compare)
        , const void *to_compare
)
{

    assert(cmp_func);
    assert(to_compare);

    while (!DLIsSameIter(from, to))
    {
        if (0 == cmp_func(DLGetData(from), to_compare))
        {
            return from;
        }
        from = DLNext(from);
    }

    return to;
}

void DLSplice(diter_t from, diter_t to, diter_t dest)
{
    dnode_t *dn_from = ITER_TO_NODE(from);
/* to is excluded */
    dnode_t *dn_to = ITER_TO_NODE(DLPrev(to));
    dnode_t *dn_dest = ITER_TO_NODE(dest);

/* un-link from and to from src */
    dn_from->prev->next = dn_to->next;
    dn_to->next->prev = dn_from->prev;

/* link from and to to dest */
    dn_from->prev = dn_dest->prev;
    dn_to->next = dn_dest;

/* link dest to src */
    dn_dest->prev->next = dn_from;
    dn_dest->prev = dn_to;
}
