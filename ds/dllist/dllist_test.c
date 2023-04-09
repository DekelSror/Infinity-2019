/*==============================================================================
Data Structures - Doubly Linked List with iterators
Tests
Dekel Sror
Review: Moti Zamir
OL66
Version 1
==============================================================================*/
#include <stdio.h> /*  printf*/
#include <string.h> /* strlen */
#include <assert.h> /* assert */

#include "dllist.h"

typedef enum { PUSH, POP } push_pop_t;
typedef enum { FRONT, BACK } front_back_t;

#define ITER_CHAR(x) (*(char *)DLGetData(x))

static int TestDLCount  (dlist_t *dl, const size_t exp_res);
static int TestDLIsEmpty(dlist_t *dl, const int exp_res);
static int TestDLGetData(diter_t dit, const char exp_res);

static void TestPopPush(dlist_t *dl, push_pop_t push_or_pop,
    front_back_t front_or_back, char *push_chars, size_t *successes);
static void TestDLForEach(dlist_t *dl, size_t i_from, size_t i_to,
    char op_arg, const char exp_res[], size_t *successes);

static void TestFind(dlist_t *dl, size_t i_from, size_t i_to
                    , char look_for, const int exp_res, size_t *successes);

static void TestSplice(dlist_t *dest_dl, dlist_t *src_dl, size_t i_from
                      , size_t i_to, size_t i_dest, const char *exp_res
                      , size_t *successes);

static int CmpChar  (const void *data, const void *to_compare);
static int CompareDLDataToString(const dlist_t *dl, const char *str);
static int PlayUChar(void *data, void *argument);

/* TestCreateInserts also performs tests*/
static void DLPrint(const dlist_t *dl);
static dlist_t *TestCreateInserts      (char items[], size_t *successes);
static diter_t GetDitToIndex(dlist_t *dl, size_t index);

int main(void)
{
    char str_test[] = { "abcdefghij" };
    char str_2[] = { "weinberg" };
    char push_chars[] = { "!@" };
    const char str_test_post_dec[] = { "abcdeghijk" };
    const char str_test_post_inc[] = { "bcdefghijk" };

    size_t total_suc = 0;
    size_t test_len = strlen(str_test);

    dlist_t *test = TestCreateInserts(str_test, &total_suc);
    dlist_t *sean = TestCreateInserts(str_2, &total_suc);

    TestDLForEach(test, 0, test_len,  1, str_test_post_inc, &total_suc);
    TestDLForEach(test, 0, 5       , -1, str_test_post_dec, &total_suc);
    TestDLForEach(test, 4, test_len, -1, str_test, &total_suc);

    TestFind(test, 0, test_len, 'g', 1, &total_suc);
    TestFind(test, 0, 4       , 'e', 0, &total_suc);
    TestFind(test, 0, test_len, 'x', 0, &total_suc);

/* TODO: compute exp_res and compare after ops */
    TestPopPush(test, PUSH, FRONT, push_chars, &total_suc);
    TestPopPush(test, PUSH, BACK, push_chars, &total_suc);
    TestPopPush(test, POP, FRONT, push_chars, &total_suc);
    TestPopPush(test, POP, BACK, push_chars, &total_suc);
    TestPopPush(test, PUSH, FRONT, push_chars, &total_suc);
    TestPopPush(test, POP, BACK, push_chars, &total_suc);
    TestPopPush(test, PUSH, BACK, push_chars, &total_suc);
    TestPopPush(test, POP, FRONT, push_chars, &total_suc);

/* "abcddfghi@" */
    TestSplice(test, test, 4, 7, 1, "adfgbcdhi@", &total_suc);
/* exp_res ^ "adfgbcdhi@" */
    TestSplice(test, test, 3, 7, 1, "agbcddfhi@", &total_suc);
/* exp_res ^ "agbcddfhi@" */
    TestSplice(sean, test, 0, 10, 7, "weinberagbcddfhi@g", &total_suc);
    DLPrint(test);
/* exp_res ^ "abcddfghi@"
    TestSplice(test, test, 1, 3, 5, "addbcfghi@", &total_suc);
 exp_res ^ "addbcfghi@" */

    DLDestroy(test);
    DLDestroy(sean);
    printf("%lu total successes\n", total_suc);

    return 0;
}

static void TestSplice(dlist_t *dest_dl, dlist_t *src_dl
                      , size_t i_from, size_t i_to, size_t i_dest
                      , const char *exp_res, size_t *successes)
{
    diter_t dit_from = { NULL };
    diter_t dit_to = { NULL };
    diter_t dit_dest = { NULL };

    assert(dest_dl);
    assert(src_dl);

    dit_from = GetDitToIndex(src_dl, i_from);
    dit_to = GetDitToIndex(src_dl, i_to);
    dit_dest = GetDitToIndex(dest_dl, i_dest);

    DLSplice(dit_from, dit_to, dit_dest);

    if (!CompareDLDataToString(dest_dl, exp_res))
    {
        printf("\nDLSplice failed, from %lu to %lu, dest %lu"
              , i_from, i_to, i_dest);
        printf("had:\n");
        DLPrint(dest_dl);
        printf("\nexpected:\n %s\n", exp_res);
    }
    else
    {
        ++*successes;
    }
}

static void TestPopPush(dlist_t *dl, push_pop_t push_or_pop,
    front_back_t front_or_back, char *push_chars, size_t *successes)
{
    size_t size_comp = 0;
    diter_t res = { NULL };

    assert(dl);

    size_comp = DLCount(dl);

    if (PUSH == push_or_pop)
    {
        if (FRONT == front_or_back)
        {
            res = DLPushFront(dl, &push_chars[0]);
            if (ITER_CHAR(res) != push_chars[0])
            {
                printf("DLPushFront failed, pushed '%c', wanted '%c'\n"
                      , ITER_CHAR(res), push_chars[0]);
            }
            else
            {
                ++*successes;
            }

        }
        else /* BACK */
        {
            res = DLPushBack(dl, &push_chars[1]);
            if (ITER_CHAR(res) != push_chars[1])
            {
                printf("DLPushFront failed, pushed '%c', wanted '%c'\n"
                      , ITER_CHAR(res), push_chars[1]);
            }
            else
            {
                ++*successes;
            }
        }
    }
    else /* (POP == push_or_pop) */
    {
        if (FRONT == front_or_back)
        {
/* value at index 1 */
            char res_data = ITER_CHAR(DLNext(DLBegin(dl)));
            DLPopFront(dl);

            if (res_data != ITER_CHAR(DLBegin(dl)))
            {
                printf("DLPopFront failed, had '%c' after popping, wanted '%c'\n"
                      , res_data, ITER_CHAR(DLBegin(dl)));
            }
            else
            {
                ++*successes;
            }
        }
        else /* BACK */
        {
            char res_data = ITER_CHAR(DLPrev(DLPrev(DLEnd(dl))));
            DLPopBack(dl);

            if (res_data != ITER_CHAR(DLPrev(DLEnd(dl))))
            {
                printf("DLPopBack failed, had '%c' after popping, wanted '%c'\n"
                      , res_data, ITER_CHAR(DLEnd(dl)));
            }
            else
            {
                ++*successes;
            }
        }
    }

/* verify push / pop by count */
    if (PUSH == push_or_pop && DLCount(dl) <= size_comp)
    {
        printf("failed to push!");
    }
    else if (POP == push_or_pop && DLCount(dl) >= size_comp)
    {
        printf("failed to pop!");
    }
    else
    {
        ++*successes;
    }
}

static void TestFind(dlist_t *dl, size_t i_from, size_t i_to
                    , char look_for, const int exp_res, size_t *successes)
{
    diter_t res = { NULL };
    diter_t dit_start = { NULL };
    diter_t dit_end = { NULL };

    assert(dl);

    dit_start = GetDitToIndex(dl, i_from);
    dit_end = GetDitToIndex(dl, i_to);

    res = DLFind(dit_start, dit_end, CmpChar, &look_for);

    if (!DLIsSameIter(res, DLEnd(dl)) && exp_res &&
        (ITER_CHAR(res) != look_for)
       )
    {
        printf("DLFind failed, had '%c', wanted %d, look_for '%c'\n"
              , ITER_CHAR(res), exp_res, look_for);
    }

    else if (DLIsSameIter(res, dit_end) && exp_res)
    {
        printf("DLFind failed, found non-existant '%c'\n"
              , look_for);
    }

    else
    {
        ++*successes;
    }
}

static void TestDLForEach(dlist_t *dl, size_t i_from, size_t i_to
                         , char op_arg, const char exp_res[], size_t *successes)
{
    int res = 0;
    diter_t dit_start = { NULL };
    diter_t dit_end = { NULL };

    assert(dl);

    dit_start = GetDitToIndex(dl, i_from);
    dit_end = GetDitToIndex(dl, i_to);

    res = DLForEach(dit_start, dit_end, PlayUChar, (void *)&op_arg);

    if (res)
    {
        printf("DLForEach failed, had %d\n", res);
    }
    else
    {
        ++*successes;
    }

    /* verify contents */
    while(!DLIsSameIter(dit_start, dit_end))
    {
        char iter_data = ITER_CHAR(dit_start);

        if (iter_data != exp_res[i_from])
        {
            printf("DLFind something went wrong, had '%c', wanted '%c'\n"
                    , iter_data, exp_res[i_from]);
        }
        else
        {
            ++*successes;
        }

        ++i_from;
        dit_start = DLNext(dit_start);
    }
}

static dlist_t *TestCreateInserts(char items[], size_t *successes)
{
    dlist_t *dl = DLCreate();
    diter_t dit = DLBegin(dl);
    size_t len = strlen(items);
    size_t i = 0;

    *successes += TestDLCount(dl, 0);
    *successes += TestDLIsEmpty(dl, 1);

    dit = DLInsert(dl, dit, &items[0]);

    *successes += TestDLGetData(dit, items[0]);

    for (i = 1; i < len; ++i)
    {
        *successes += TestDLCount(dl, i);
        dit = DLInsertAfter(dl, dit, &items[i]);
        *successes += TestDLIsEmpty(dl, 0);
        *successes += TestDLGetData(dit, items[i]);
    }

    return dl;
}

/* small units - are called by larger ones */
static int TestDLCount(dlist_t *dl, const size_t exp_res)
{
    size_t res = 0;

    assert(dl);

    res = DLCount(dl);

    if (res != exp_res)
    {
        printf("DLCount failed, had '%lu', exp_res %lu\n"
                , res, exp_res);

        return 0;
    }

    return 1;
}

static int TestDLIsEmpty(dlist_t *dl, const int exp_res)
{
    int res = 0;

    assert(dl);

    res = DLIsEmpty(dl);

    if (res != exp_res)
    {
        printf("TestDLIsEmpty failed, had %d, exp_res %d\n"
                , res, exp_res);

        return 0;
    }

    return 1;
}

static int TestDLGetData(diter_t dit, const char exp_res)
{
    char res = ITER_CHAR(dit);

    if ((res != exp_res))
    {
        printf("TestDLGetData failed, had '%c', exp_res '%c'\n"
                , res, exp_res);

        return 0;
    }

    return 1;
}

/* test cmp_func */
static int CmpChar(const void *data, const void *to_compare)
{
    return (*(char *)data - *(char *)to_compare);
}

/* test operation_func */
static int PlayUChar(void *data, void *argument)
{
    assert(data);

    *(char *)data += *(char *)argument;

    return 0;
}

/* utility - to set to and from @ DLForEach, DLFind, DLSplice tests */
static diter_t GetDitToIndex(dlist_t *dl, size_t index)
{
    diter_t dit = DLBegin(dl);

    while (index)
    {
        dit = DLNext(dit);
        --index;
    }

    return dit;
}

static int CompareDLDataToString(const dlist_t *dl, const char *str)
{
    diter_t dit = DLBegin(dl);

    while (*str && !DLIsSameIter(dit, DLEnd(dl)))
    {
        if (!CmpChar((void *)str, DLGetData(dit)))
        {
            return 0;
        }
        dit = DLNext(dit);
        ++str;
    }

    return 1;
}

static void DLPrint(const dlist_t *dl)
{
    diter_t dit = DLBegin(dl);

    while (!DLIsSameIter(dit, DLEnd(dl)))
    {
        printf("'%c', ", *(char*)DLGetData(dit));
        dit = DLNext(dit);
    }
}
