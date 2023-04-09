/*==============================================================================
Data Structures - Singly Linked List
Tests
Dekel Sror
Review: Maor Alankri
OL66
Version 2
==============================================================================*/
#include <stdio.h> /* printf */
#include <ctype.h> /* tolower */

#include "linked_list.h"

#define UNUSED(x) (void)(x)
#define ARR_LEN(x) (sizeof(x) / sizeof(x[0]))

static node_t *MakeIList(size_t len);
static size_t TestInsert(void);
static size_t TestRemove(void);
static size_t TestHasLoop(void);
static size_t TestSumForEach(void);
static size_t TestInterSection(void);
static size_t TestFind(void);
static size_t TestFlip(void);
static int TestCount(node_t *head, size_t exp_res);

int SumFunc(void *node_data, void *sum);
int CompCharsNoCase(const void *data, const void* arg);

#define LIST_LEN (7)

static char data_entries[LIST_LEN] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G' };
static char data_signs[] = { '!', '?' };

int main(void)
{
    size_t total_pass = 0;
    total_pass += TestInsert();
    total_pass += TestRemove();
    total_pass += TestSumForEach();
    total_pass += TestInterSection();
    total_pass += TestHasLoop();
    total_pass += TestFind();
    total_pass += TestFlip();

    printf("total tests passed: %lu\n", total_pass);

    return 0;
}

/* total of 5 tests per call - 3 counts and 2 insert checks */
static size_t TestInsert(void)
{
    node_t *test_head = MakeIList(LIST_LEN);
    node_t *third = test_head->next->next;
    node_t *test_insert_pre = ListCreateNode(&data_signs[0], NULL);
    node_t *test_insert_post = ListCreateNode(&data_signs[1], NULL);
    node_t *res_insert = NULL;
    size_t successes = 0;

    successes += TestCount(test_head, LIST_LEN);
/* 'A', 'B', <'C'>, 'D', 'E', 'F', 'G' */
    res_insert = ListInsert(test_insert_pre, third);
/* 'A', 'B', <'!'>, 'C', 'D', 'E', 'F', 'G' */
    if ('!' != *(char *)res_insert->data)
    {
        printf("failed insert before, have '%c', want '!'\n"
                , *(char *)res_insert->data);
    }
    else
    {
        ++successes;
    }

    successes += TestCount(test_head, LIST_LEN + 1);

    res_insert = ListInsertAfter(test_insert_post, third);
/* 'A', 'B', <'!'>, '?', 'C', 'D', 'E', 'F', 'G' */
    if ('?' != *(char *)(res_insert->next->data))
    {
        printf("failed insert after\n");
    }
    else
    {
        ++successes;
    }

    successes += TestCount(test_head, LIST_LEN + 2);

    ListFreeAll(test_head);

    return successes;
}

/* total of 5 tests per call - 3 counts and 2 remove checks */
static size_t TestRemove(void)
{
    node_t *test_head = MakeIList(LIST_LEN);
    node_t *fourth = test_head->next->next->next;
    char res = 0;
    size_t successes = 0;

    successes += TestCount(test_head, LIST_LEN);
    res = *(char *)ListRemove(fourth)->data;
    successes += TestCount(test_head, LIST_LEN - 1);

    if ('E' != res)
    {
        printf("ListRemove failed! had '%c', exp_res '%c'\n"
                , res, *(char *)test_head->next->next->next->data);
    }
    else
    {
        ++successes;
    }

    res = *(char *)ListRemoveAfter(fourth)->data;
    successes += TestCount(test_head, LIST_LEN - 2);
    if ('E' != res)
    {
        printf("ListRemoveAfter failed! had '%c', exp_res '%c'\n"
                , res, *(char *)(test_head->next->next->next->data));
    }
    else
    {
        ++successes;
    }

    ListFreeAll(test_head);

    return successes;
}


static size_t TestSumForEach(void)
{
    size_t exp_res = 0;
    node_t *test_head = MakeIList(LIST_LEN);
    node_t *runner = test_head;
    size_t sum_res = 0;
    size_t successes = 0;
    int res = 0;
/* calculate exp_res */
    while(runner)
    {
        exp_res += (size_t)*(char *)runner->data;
        runner = runner->next;
    }

    res = ListForEach(test_head, SumFunc, (void *)&sum_res);

/* res of the foreach itself */
    if (0 != res)
    {
        printf("well shit\n");
    }
    else
    {
        ++successes;
    }

/* did the sum compute correctly */
    if (sum_res != exp_res)
    {
        printf("ListForEach failed to sum\n");
    }
    else
    {
        ++successes;
    }

    ListFreeAll(test_head);

    return successes;
}

static int TestCount(node_t *head, size_t exp_res)
{
    size_t res = ListCount(head);

    if (exp_res != res)
    {
        printf("ListCount failed! had %lu, exp_res %lu\n", res, exp_res);
        return 0;
    }

    return 1;
}

int SumFunc(void *node_data, void *sum)
{
    size_t *p_sum = (size_t *)sum;

    *p_sum += (size_t)*(char *)node_data;

    return 0;
}

static node_t *MakeIList(size_t len)
{
    size_t i = 0;
    node_t *test_head = ListCreateNode(NULL, NULL);
    node_t *runner = test_head;

    for (i = 1; i < len; ++i)
    {
        runner->data = &data_entries[i - 1];
        runner->next = ListCreateNode(NULL, NULL);
        runner = runner->next;
    }
    runner->data = &data_entries[i - 1];

    return test_head;
}



static size_t TestInterSection(void)
{
    node_t *test_1 = MakeIList(LIST_LEN);
    node_t *test_2 = MakeIList(2);
    node_t *fourth_1 = test_1->next->next->next;
    node_t *res = NULL;
    size_t successes = 0;

    test_2->next->next = fourth_1;

    res = (node_t *)ListFindIntersection(test_1->next, test_2);

    if ('D' != *(char *)res->data)
    {
        printf("ListFindIntersection failed! had '%c' | %p, expected '%c' | %p\n"
                , *(char *)res->data, (void *)res->next
                , *(char *)fourth_1->data, (void *)fourth_1->next);
    }
    else
    {
        ++successes;
    }

    test_2->next->next = NULL;

    res = (node_t *)ListFindIntersection(test_1->next, test_2);
    if (res)
    {
        printf("ListFindIntersection failed! had '%c' | %p , expected NULL\n"
            ,*(char *)res->data, (void *)res->next);
    }

    ListFreeAll(test_1);
    ListFreeAll(test_2);

    return successes;
}

static size_t TestHasLoop(void)
{
    size_t successes = 0;
    node_t *test_head = MakeIList(LIST_LEN);

/* save 5th element */
    node_t *keeper = test_head->next->next->next->next;

/* make a loop - point fourth element's next to head */
    test_head->next->next->next->next = test_head;

    if(!ListHasLoop(test_head))
    {
        printf("ListHasLoop failed to find loop\n");
    }
    else
    {
        ++successes;
    }

    test_head->next->next->next->next = keeper;

    if(ListHasLoop(test_head))
    {
        printf("ListHasLoop failed to NOT find loop\n");
    }
    else
    {
        ++successes;
    }

    ListFreeAll(test_head);

    return successes;
}

int CompCharsNoCase(const void *data, const void* arg)
{
    return tolower(*(char *)data) == tolower(*(char *)arg);
}

static size_t TestFind(void)
{
    node_t *test_head = MakeIList(LIST_LEN);
    node_t *res = NULL;
    int res_cmp_1 = 'c'; /* is in list     */
    int res_cmp_2 = 'R'; /* is not in list */
    size_t successes = 0;

    res = ListFind(test_head, (void *)&res_cmp_1, CompCharsNoCase);

    if (!res)
    {
        printf("ListForEach failed to find 'c' in list\n");
    }
    else
    {
        ++successes;
    }

     res = ListFind(test_head, (void *)&res_cmp_2, CompCharsNoCase);

    if (res)
    {
        printf("ListForEach found a non-existant 'R' in list\n");
    }
    else
    {
        ++successes;
    }

    ListFreeAll(test_head);

    return successes;
}

static size_t TestFlip(void)
{
    node_t *test_head = MakeIList(LIST_LEN);

    ListPrint(test_head);

    test_head = ListFlip(test_head);

    ListPrint(test_head);

    ListFreeAll(test_head);

    return 0;
}
