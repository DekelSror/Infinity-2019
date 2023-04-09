#include <stdio.h>
#include <stdlib.h>

int *IsSumFound(int arr[], size_t arr_len, int sum);

int main()
{
    int test_arr[] = { 2,4,5,78,200,801 };
    int *test = IsSumFound(test_arr, 6, 82);
    size_t i = 0;

    for (i = 0; i < 3; ++i)
    {
        printf("%d\n", test[i]);
    }

    free(test);
    return 0;
}



/* caller is to free malloc'd memory */
int *IsSumFound(int arr[], size_t arr_len, int sum)
{
    int *a_head = arr;
    int *a_tail = arr + arr_len;
    size_t t_sum = 0;
    int *res = (int*)malloc(3*sizeof(int));

    if(!res)
    {
        printf("malloc failed!\n");
        exit(1);
    }

    res[0] = 0; res[1] = 0; res[2] = 0;

    while(a_head < a_tail)
    {
        t_sum = *a_head + *a_tail;

        if(sum == t_sum)
        {
            res[0] = 1;
            res[1] = a_head - arr;
            res[2] = a_tail - arr;
            return res;
        }

        else if(sum > t_sum)
        {
            ++a_head;
        }

        else
        {
            --a_tail;
        }
    }

    return res;
}
