/*==============================================================================
Data Structures - Queue based on linked_list
Tests
Dekel Sror
Review: Tzvi Cubac
Version 1
==============================================================================*/
#include <stdio.h> /* ptintf */
#include <string.h> /* memcmp */

#include "queue.h"
#include "linked_list.h"

/* test data */
static char test_arr[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j' };

#define ARR_LEN(x) (sizeof(x) / sizeof(x[0]))

/* integrates enq, deq, size, peek, isempty */
static size_t TestQScenario (void);
static int    TestQEmpty    (queue_t *q, int exp_res);
static int    TestQSize     (queue_t *q, size_t exp_res);
static int    TestQPeek     (queue_t *q, char exp_res, const char *msg);
static int    TestQEnqueue  (queue_t *q, void *data);

/* separate test for append */
static size_t TestQAppend   (void);

int main(void)
{
    size_t total_successes = TestQScenario();
    printf("total_successes: %lu\n", total_successes);

    TestQAppend();

    return 0;
}

/* create a new queue. push test_arr to it. pop everything out */
/* on every iteration also check size, isempty, and peek */
static size_t TestQScenario(void)
{
    queue_t *test = QCreate();
    size_t successes = 0;
    size_t i = 0;

    successes += TestQEmpty(test, 1);

    for ( i = 0;  i < ARR_LEN(test_arr); ++i)
    {
        successes += TestQSize(test, i);
        successes += TestQEnqueue(test, (void *)&test_arr[i]);
        successes += TestQEmpty(test, 0);
        successes += TestQPeek(test, 'a', "while adding");
    }

    for ( i = ARR_LEN(test_arr);  i > 0 ; --i)
    {
        successes += TestQSize(test, i);
        successes += TestQPeek(test, test_arr[ARR_LEN(test_arr) - i], "while popping");
        successes += TestQEmpty(test, 0);
        QDequeue(test);
    }

    successes += TestQEmpty(test, 1);

    QDestroy(test);

    return successes;
}

static size_t TestQAppend(void)
{
    queue_t *test_dest = QCreate();
    queue_t *test_src = QCreate();

    size_t i = 0;

    for (i = 0; i < ARR_LEN(test_arr) / 2; ++i)
    {
        QEnqueue(test_dest, (void *)&test_arr[i]);
        QEnqueue(test_src, (void *)&(test_arr[i + (ARR_LEN(test_arr) / 2)]));
    }

    printf("Append test. test_dest Before -\n");
    QPrint(test_dest);
    QAppend(test_dest, test_src);
    printf("test_dest After\n");
    QPrint(test_dest);
    QDestroy(test_dest);
    QDestroy(test_src);

    return 0;
}

/* unit tests */

static int TestQEnqueue(queue_t *q, void *data)
{
    if (QEnqueue(q, data))
    {
        printf("QEnqueue failed\n");
        return 0;
    }

    return 1;
}

static int TestQSize(queue_t *q, size_t exp_res)
{
    size_t res = QSize(q);

    if (res != exp_res)
    {
        printf("QSize failed, had %lu, exp_res %lu\n", res, exp_res);
        return 0;
    }

    return 1;
}

static int TestQPeek(queue_t *q, char exp_res, const char *msg)
{
    char res = *(char *)QPeek(q);

    if (res != exp_res)
    {
        printf("QPeek failed %s, had '%c', exp_res '%c'\n",msg, res, exp_res);
        return 0;
    }

    return 1;
}

static int TestQEmpty(queue_t *q, int exp_res)
{
    int res = QIsEmpty(q);

    if (res != exp_res)
    {
        printf("QIsEmpty failed, had %d, exp_res %d\n", res, exp_res);
        return 0;
    }

    return 1;
}
