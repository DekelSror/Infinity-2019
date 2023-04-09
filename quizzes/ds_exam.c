

/*
    static queue - circular buffer approach
*/
#include <stdio.h>

#define Q_SIZE (5)

typedef struct queue_s
{
    char q[Q_SIZE];
    size_t elements_in_q;
    size_t first_element;
} queue_t;


int QPushChar(queue_t *q, char c)
{
    size_t spot = (q->first_element + q->elements_in_q) % Q_SIZE;

    if (spot == q->first_element)
    {
        printf("full queue\n");

        return 1;
    }

    q->q[spot] = c;

    ++q->elements_in_q;

    return 0;
}

char QPopChar(queue_t *q)
{
    char result = q->q[q->first_element + 1];

    --q->elements_in_q;
    ++q->first_element;

    return result;
}

/*
    find largest sum - dynamic programming
*/

typedef struct sum_res_s
{
    size_t index_start;
    size_t index_end;
    long sum;
} sum_res_t;



sum_res_t FindLargestSum(const long *arr, size_t len)
{
    size_t start = 0;
    long interval_sum = 0;
    size_t i = 0;

    sum_res_t result = { 0, 0, 0 };

    for (i = 0; i < len; ++i)
    {
        interval_sum += arr[i];

        if (arr[i] >= interval_sum)
        {
            interval_sum = arr[i];
            start = i + 1;
        }

        if (interval_sum > result.sum)
        {
            result.sum = interval_sum;
            result.index_start = start;
            result.index_end = i;
        }

    }

    return result;
}


int main(void)
{
    queue_t test = { { 0 }, 1, 0};
    int push_res = 0;
    char input = 'a';

    long dyn_test[] = { 0, 1, 1, -4, 5, 8, -8, 9, 0, -7 };
    sum_res_t dyn_res = FindLargestSum(dyn_test, 10);

    printf("sum %ld, for %lu to %lu\n", dyn_res.sum, dyn_res.index_start, dyn_res.index_end);

    while (!push_res)
    {
        push_res = QPushChar(&test, input);

        ++input;
    }

    while (test.elements_in_q > 1)
    {
        printf("first in line: '%c'\n", QPopChar(&test));
    }

    return 0;
}
