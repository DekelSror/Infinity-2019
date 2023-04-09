/*==============================================================================
Data Structures - Priotiy Queue
Tests
Dekel Sror
Review: Tal Shabtai
OL66
Version 1
==============================================================================*/
#include <stdio.h>
#include <assert.h>

#include "priority_q.h"
#include "useful.h"

static int TestSize(pq_t *pq, size_t exp_res);
static int TestIsEmpty(pq_t *pq, int exp_res);
static int TestPeek(pq_t *pq, int exp_res);

static size_t TestEnqDeq(void);

static int IsDivByThree (const void *data1, const void *data2);
static int IsIntFive(const void *data, void *arg);

int main(void)
{
    size_t total_passed = 0;

    total_passed += TestEnqDeq();

    printf("passed %lu tests\n", total_passed);

    return 0;
}

static size_t TestEnqDeq(void)
{
    int test_data[] = { 0, 8, 18, 5, 6, 2, 2, 21, 100 };
    size_t passed = 0;

    pq_t *test = PriorityQCreate(IsDivByThree);

    passed += TestSize(test, 0);
    passed += TestIsEmpty(test, 1);

    PriorityQEnqueue(test, &test_data[0]);
    passed += TestIsEmpty(test, 0);
    passed += TestSize(test, 1);
    passed += TestPeek(test, 0);
    PriorityQEnqueue(test, &test_data[1]);
    passed += TestSize(test, 2);
    passed += TestPeek(test, 0);

    PriorityQEnqueue(test, &test_data[2]);
    passed += TestPeek(test, 18);
    PriorityQEnqueue(test, &test_data[3]);
    PriorityQEnqueue(test, &test_data[4]);
    PriorityQEnqueue(test, &test_data[5]);

    passed += TestPeek(test, 6);
    PriorityQDequeue(test);
    passed += TestSize(test, 5);
    passed += TestPeek(test, 18);
    PriorityQDequeue(test);
    passed += TestPeek(test, 0);


    PriorityQErase(test, IsIntFive, NULL);

    PriorityQClear(test);

    PriorityQDestroy(test);

    return passed;
}

static int IsIntFive(const void *data, void *arg)
{
    UNUSED(arg);

    return (5 == (*(int *)data));
}

static int IsDivByThree (const void *data1, const void *data2)
{
    int num1 = *(int *)data1;
    int num2 = *(int *)data2;

    return ((0 == (num1 % 3)) && (0 != (num2 % 3)));
}

static int TestPeek(pq_t *pq, int exp_res)
{
    int res = *(int *)PriorityQPeek(pq);

    if (res != exp_res)
    {
        printf("Peek failed, had %d, exp_res %d\n", res, exp_res);

        return 0;
    }

    return 1;
}

static int TestSize(pq_t *pq, size_t exp_res)
{
    size_t res = PriorityQSize(pq);

    if (res != exp_res)
    {
        printf("Size failed, had %lu, exp_res %lu\n", res, exp_res);

        return 0;
    }

    return 1;
}

static int TestIsEmpty(pq_t *pq, int exp_res)
{
    int res = PriorityQIsEmpty(pq);

    if (res != exp_res)
    {
        printf("IsEmpty failed, had %d, exp_res %d\n", res, exp_res);

        return 0;
    }

    return 1;
}
