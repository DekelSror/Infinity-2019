/*==============================================================================
Data Structures - Sorted List
Module
Dekel Sror
Review: Tal Shabtai
OL66
Version 1
==============================================================================*/
#include <stdlib.h> /* malloc, NULL, free */
#include <assert.h> /* assert             */

#include "dllist.h"
#include "sorted_ll.h"

#define ITER_CAST(x, y) ((x.info) = (y.info))
#define MAX2(a,b) (((a) >= (b)) ? (a) : (b))

struct sortedlist_s
{
    dlist_t *list;
    is_before_t is_before;
};

static sliter_t DiterToSliter(diter_t dit)
{
    sliter_t res = { 0 };

    ITER_CAST(res, dit);

    return res;

}

static diter_t SliterToDiter(sliter_t slit)
{
    diter_t res = { 0 };

    ITER_CAST(res, slit);

    return res;

}

sortedlist_t *SortedListCreate(is_before_t before_func)
{
    sortedlist_t *new_sortedll = { 0 };

    assert(before_func);

    new_sortedll = (sortedlist_t *)malloc(sizeof(sortedlist_t));

    if (NULL == new_sortedll)
    {
        return NULL;
    }

    new_sortedll->list = DLCreate();

    if (NULL == new_sortedll->list)
    {
        free(new_sortedll);

        return NULL;
    }

    new_sortedll->is_before = before_func;

    return new_sortedll;
}

void SortedListDestroy(sortedlist_t *list)
{
    assert(list);

    DLDestroy(list->list);

    free(list);

    list = NULL;
}

size_t SortedListCount(const sortedlist_t *list)
{
    assert(list);

    return DLCount(list->list);
}

int SortedListIsEmpty(const sortedlist_t *list)
{
    assert(list);

    return DLIsEmpty(list->list);
}

sliter_t SortedListInsert(sortedlist_t *list, void *data)
{
	sliter_t iter = SortedListBegin(list);

	while (!SortedListIsSameIter(iter,SortedListEnd(list))
            && !(list->is_before(data,SortedListGetData(iter))))
		{
			iter = SortedListNext(iter);
		}

	iter = DiterToSliter(DLInsert(list->list, SliterToDiter(iter), data));

	return iter;
}


void *SortedListPopBack(sortedlist_t *list)
{
    void *data_keep = NULL;

    assert(list);

    data_keep = DLGetData(DLPrev(DLEnd(list->list)));

    DLPopBack(list->list);

    return data_keep;
}

void *SortedListPopFront(sortedlist_t *list)
{
    void *data_keep = NULL;

    assert(list);

    data_keep = DLGetData(DLBegin(list->list));

    DLPopFront(list->list);

    return data_keep;
}

int SortedListForEach
                    (
                    sliter_t from,
                    sliter_t to,
                    s_operation_t opt_func,
                    void *arg
                    )
{
    diter_t d_from = SliterToDiter(from);
    diter_t d_to = SliterToDiter(to);

    assert(opt_func);
    assert(arg);

    ITER_CAST(d_from, from);
    ITER_CAST(d_to, to);

    return DLForEach(d_from, d_to, opt_func, arg);
}

sliter_t SortedListFind
                      (
                      sliter_t from,
                      sliter_t to,
                      is_match_t is_match,
                      const void *to_find,
                      void *arg
                      )
{
    while (!SortedListIsSameIter(from, to))
    {
        int res = is_match(SortedListGetData(from), to_find, arg);

        if (res)
        {
            return from;
        }

        from = SortedListNext(from);
    }

    return to;
}

/* assumes same data types, same sorting method */
void SortedListMerge(sortedlist_t *dest, sortedlist_t *src)
{
    sliter_t dest_pre = { 0 };
    sliter_t dest_next_seg = { 0 };
    sliter_t src_from = { 0 };
    sliter_t src_to = { 0 };

    assert(dest);
    assert(src);

    ITER_CAST(src_from, src_to);

    dest_pre = SortedListBegin(dest);
    dest_next_seg = dest_pre;
    src_from = SortedListBegin(src);
    src_to = src_from;

    while (!SortedListIsSameIter(dest_next_seg, SortedListEnd(dest)))
    {

        while (!dest->is_before(SortedListGetData(dest_pre), SortedListGetData(src_to)))
        {
            src_to = SortedListNext(src_to);
        }

        DLSplice(SliterToDiter(src_from),
                 SliterToDiter(src_to),
                 SliterToDiter(dest_pre)
             );

        while(dest->is_before(SortedListGetData(dest_pre), SortedListGetData(src_from)))
        {
         src_from = SortedListNext(src_from);
        }
    }
}

sliter_t SortedListBegin(sortedlist_t *list)
{
    sliter_t sort_iter = { 0 };

    assert(list);

    sort_iter = DiterToSliter(DLBegin(list->list));

    return sort_iter;
}

sliter_t SortedListEnd(sortedlist_t *list)
{
    sliter_t sort_iter = { 0 };

    assert(list);

    sort_iter = DiterToSliter(DLEnd(list->list));

    return sort_iter;
}

sliter_t SortedListNext(sliter_t iter)
{
    diter_t dit = { 0 };

    dit = SliterToDiter(iter);

    iter = DiterToSliter(DLNext(dit));

    return iter;
}

sliter_t SortedListPrev(sliter_t iter)
{
    diter_t dit = { 0 };

    dit = SliterToDiter(iter);

    iter = DiterToSliter(DLPrev(dit));

    return iter;
}

sliter_t SortedListErase(sliter_t iter)
{
    diter_t dit = { 0 };

    dit = SliterToDiter(iter);
    iter = DiterToSliter(DLNext(dit));

    DLErase(dit);

    return iter;
}

int SortedListIsSameIter(sliter_t iter1, sliter_t iter2)
{
    return iter1.info == iter2.info;
}

void *SortedListGetData(sliter_t iter)
{
    diter_t dit = { 0 };

    dit = SliterToDiter(iter);

    return DLGetData(dit);
}
