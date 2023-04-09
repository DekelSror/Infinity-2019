/*==============================================================================
Data Structures - Sorted List
Tests
Dekel Sror
Review: Tal Shabtai
OL66
Version 1
==============================================================================*/
#include <stdio.h>  /* printf             */
#include <assert.h> /* assert             */
#include <stdlib.h> /* malloc, free, NULL */

#include "sorted_ll.h"
#include "useful.h"

typedef enum { FRONT, BACK } front_back_t;

static sortedlist_t *TestCreateInsert
                                    (
                                    const long *node_data,
                                    long *data_buffer,
                                    is_before_t sort_method,
                                    size_t list_len,
                                    size_t *successes
                                    );

static void TestPops
                    (
                    sortedlist_t *list, front_back_t which_end,
                    long exp_res, size_t *successes
                    );

static void TestIsSameIter(sliter_t it1, sliter_t it2, int exp_res
                           , size_t *successes);

static void TestErase(sortedlist_t *list, size_t i_to_erase, long exp_data
                     , size_t *successes);

static void TestForEach(sortedlist_t *list,
                         size_t index_from, size_t index_to, s_operation_t func,
                         long arg, long *exp_res, size_t *successes);

static void TestFind(sortedlist_t *list, size_t i_from, size_t i_to,
                     long div_by, size_t exp_res, size_t *successes);

static void TestIsempty(sortedlist_t *list, int exp_res, size_t *successes);
static void TestCount(sortedlist_t *list, size_t exp_res, size_t *successes);
static void TestGetData(sliter_t iter, long exp_res, size_t *successes);

/* is_before_t */
static int IsLongSmaller(const void *data, const void *arg);
/* s_operation_t */
static int OptAddToLong(void *data, void *arg);
/* is_match_t */
static int CountDivLongs(const void *data, const void *to_cmp, void *arg);

static void SortedListPrint(sortedlist_t *list);
static sliter_t GetSLIndex(sortedlist_t *list, size_t index);

int main(void)
{
    size_t total_pass = 0;
    long foreach_arg = 6l;

    const long l_data[] = { 1, -1, 2, -2, 3, -3, 4, -4 };
    long l_exp_res[] = { -4, -3, -2, -1, 1, 2, 3, 4 };
    long *l_data_cpy = NULL;

    sortedlist_t *test = { 0 };

/* test #1 - foreach */
    l_data_cpy = (long *)malloc(sizeof(long) * ARR_LEN(l_data));

    test = TestCreateInsert(l_data, l_data_cpy, IsLongSmaller,
                                          ARR_LEN(l_data), &total_pass);

    TestForEach(test, 0, SortedListCount(test), OptAddToLong,
                foreach_arg, l_exp_res, &total_pass);

    SortedListDestroy(test);
    free(l_data_cpy);

/* test #2 - erase and pop */
    l_data_cpy = (long *)malloc(sizeof(long) * ARR_LEN(l_data));

    test = TestCreateInsert(l_data, l_data_cpy, IsLongSmaller,
                                          ARR_LEN(l_data), &total_pass);

    TestFind(test, 0, SortedListCount(test), 2, 4, &total_pass);

    TestFind(test, 0, 0, 2, 0, &total_pass);

    TestFind(test, 0, 4, 2, 2, &total_pass);

    TestErase(test, 5,  3, &total_pass);
    TestErase(test, 5, 4, &total_pass);

    TestPops(test, FRONT, -4, &total_pass);
    TestPops(test, BACK ,  4, &total_pass);
    TestPops(test, BACK ,  1, &total_pass);

    SortedListDestroy(test);
    free(l_data_cpy);

    printf("total %lu tests passed\n", total_pass);

    return 0;
}

static void TestPops
                    (
                    sortedlist_t *list, front_back_t which_end,
                    long exp_res, size_t *successes
                    )
{
    long res = 0;

    const char *s_front = "Front";
    const char *s_back  = "Back";
    size_t list_len = 0;

    assert(list);

    list_len = SortedListCount(list);

    if (FRONT == which_end)
    {
        res = *(long *)SortedListPopFront(list);
    }
    else /* BACK */
    {
        res = *(long *)SortedListPopBack(list);
    }

    if (SortedListCount(list) >= list_len)
    {
        printf("failed to pop!\n");
    }

    if (res != exp_res)
    {
        const char *s = (which_end == FRONT) ? s_front : s_back;
        printf("SoretedListPop%s failed, had %ld, exp_res %ld\n"
              , s, res, exp_res);
    }
    else
    {
        ++*successes;
    }

}
static void TestErase(sortedlist_t *list, size_t i_to_erase, long exp_data
                      , size_t *successes)
{
    sliter_t slit = SortedListBegin(list);
    long res = 0;
    size_t i = 0;
    size_t list_len = SortedListCount(list);

    for ( i = 0; i < i_to_erase; ++i)
    {
        slit = SortedListNext(slit);
    }

    res = *(long *)SortedListGetData(SortedListErase(slit));

    if (SortedListCount(list) >= list_len)
    {
        printf("failed to erase!\n");
    }

    if (res != exp_data)
    {
        printf("SoretedListErase failed, had %ld, exp_res %ld\n"
              , res, exp_data);
    }
    else
    {
        ++*successes;
    }


    if (res != exp_data)
    {
        printf("SortedListErase failed, returned %ld, exp_res %ld\n"
              , res, exp_data);
    }
    else
    {
        ++*successes;
    }
}

/* is_before_t function */
static int IsLongSmaller(const void *data, const void *arg)
{
    return *(long *)data <= *(long *)arg;
}

static sliter_t GetSLIndex(sortedlist_t *list, size_t index)
{
    sliter_t iter = SortedListBegin(list);

    while (index)
    {
        iter = SortedListNext(iter);
        --index;
    }

    return iter;
}

static void TestFind(sortedlist_t *list, size_t i_from, size_t i_to,
                     long div_by, size_t exp_res, size_t *successes)
{
    sliter_t find_res = { 0 };
    size_t counter = 0;

    sliter_t iter_from = GetSLIndex(list, i_from);
    sliter_t iter_to = GetSLIndex(list, i_to);

    assert(list);

    find_res = SortedListFind(iter_from, iter_to, CountDivLongs, &div_by, &counter);

    (void)find_res;

    if (counter != exp_res)
    {
        printf("SortedListFind failed to find all longs divisible by %ld\
                \n had %lu, exp_res %lu, from %lu to %lu"
                , div_by, counter, exp_res, i_from, i_to);
    }
    else
    {
        ++*successes;
    }
}

/* is_match_t function */
static int CountDivLongs(const void *data, const void *to_cmp, void *arg)
{
    size_t *arg_as_counter = (size_t *)arg;

    if (NULL == data)
    {
        return 1;
    }

    *arg_as_counter += (0 == (*(long *)data % *(long *)to_cmp));

    return 0;
}
/* s_operation_t function */
static int OptAddToLong(void *data, void *arg)
{
    if (!arg || !data)
    {
        return 1; /* BAD_ARGS */
    }

    *(long *)data += *(long *)arg;

    return 0;
}

static void TestForEach(sortedlist_t *list,
                        size_t index_from, size_t index_to, s_operation_t func,
                        long arg, long *exp_res, size_t *successes)
{
    int res = 0;
    size_t i = 0;
    long *run_exp_res = exp_res;
    sliter_t slit = { 0 };
    sliter_t it_from = { 0 };
    sliter_t it_to = { 0 };

    assert(list);

    slit = SortedListBegin(list);

/* get list and exp_res to desired from (and to) indices */
    for (i = 0; i < index_from; ++i)
    {
        ++run_exp_res;
        slit = SortedListNext(slit);
    }
    it_from.info = slit.info;

    for (; i < index_to; ++i)
    {
        *run_exp_res += arg;
        ++run_exp_res;
        slit = SortedListNext(slit);
    }

    it_to.info = slit.info;

    res = SortedListForEach(it_from, it_to, func, &arg);

/* check functoin failure */
    if (0 != res)
    {
        printf("SortedListForEach out right failed!\n");
    }
    else
    {
        ++*successes;
    }

/* check operation results */
    slit = SortedListBegin(list);
    run_exp_res = exp_res;

    for (i = 0; i < (index_to - index_from); ++i)
    {
        long iter_data = *(long *)SortedListGetData(slit);
        if (iter_data != *run_exp_res)
        {
            printf("SortedListForEach failed, had %ld, exp_res %ld\n"
                  , iter_data, *run_exp_res);
            SortedListPrint(list);
        }
        else
        {
            ++*successes;
        }
        ++run_exp_res;
        slit = SortedListNext(slit);
    }
}

static sortedlist_t *TestCreateInsert
                                    (
                                    const long *node_data,
                                    long *data_buffer,
                                    is_before_t sort_method,
                                    size_t list_len,
                                    size_t *successes
                                    )
{
    sortedlist_t *new_sl = SortedListCreate(sort_method);
    sliter_t filler = SortedListBegin(new_sl);

    size_t i = 0;

    TestIsempty(new_sl, 1, successes);
    TestIsSameIter(filler, SortedListEnd(new_sl), 1, successes);

    for (i = 0; i < list_len; ++i)
    {
        *data_buffer = *node_data;

        TestCount(new_sl, i, successes);

        filler = SortedListInsert(new_sl, data_buffer);

        TestGetData(filler, *node_data, successes);
        TestIsSameIter(filler, SortedListEnd(new_sl), 0, successes);

        ++data_buffer;
        ++node_data;
    }

    TestIsempty(new_sl, 0, successes);

    return new_sl;
}

static void TestIsSameIter(sliter_t it1, sliter_t it2, int exp_res
                           , size_t *successes)
{
    int res = SortedListIsSameIter(it1, it2);

    if (res != exp_res)
    {
        printf("SortedListIsSameIter failed, had %d, exp_res %d\n"
              , res, exp_res);
    }
    else
    {
        ++*successes;
    }
}

static void TestIsempty(sortedlist_t *list, int exp_res, size_t *successes)
{
    int res = 0;

    assert(list);

    res = SortedListIsEmpty(list);

    if (res != exp_res)
    {
        printf("SortedListIsEmpty failed, had %d, exp_res %d\n"
              , res, exp_res);
    }
    else
    {
        ++*successes;
    }
}

static void TestCount(sortedlist_t *list, size_t exp_res, size_t *successes)
{
    size_t res = 0;

    assert(list);

    res = SortedListCount(list);

    if (res != exp_res)
    {
        printf("SortedListCount failed, jad %lu, exp_res %lu\n"
              , res, exp_res);
    }
    else
    {
        ++*successes;
    }
}

static void TestGetData(sliter_t iter, long exp_res, size_t *successes)
{
    long res = *(long *)SortedListGetData(iter);

    if (res != exp_res)
    {
        printf("SortedListGetData failed, had %ld, exp_res %ld\n"
               ,res, exp_res);
    }
    else
    {
        ++*successes;
    }
}

static void SortedListPrint(sortedlist_t *list)
{
    sliter_t slit = SortedListBegin(list);

    printf("\n");

    while (!SortedListIsSameIter(slit, SortedListEnd(list)))
    {
        printf("%ld, ", *(long *)SortedListGetData(slit));
        slit = SortedListNext(slit);
    }
    printf("\n\n");
}
