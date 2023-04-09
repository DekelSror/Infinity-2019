#include <stdlib.h>
#include <stdio.h> /* printf */

/*========================================================================*/
/* Quiz #6                                                                */
/* Dynamic Programming                                                    */
/* Stock Market                                                           */
/* Dekel Sror */
/*========================================================================*/

#define ARR_LEN(x) (sizeof(x) / sizeof(x[0]))

typedef struct stock_ret_ stock_ret_s;
struct stock_ret_
{
    int sell;
    int buy;
    int margin;
};

static const int tests[3][11] =
{
    {5,  2,  8,  5,  4, 10, 65, 4 , 1,  2, 44 },
    {10, 54, 10, 52, 8, 89, 1,  54, 55, 0, 0  },
    {10, 11, 12, 50, 1, 0,  5,  20, 29, 0, 44 }
};


static const stock_ret_s ex_res[] =
{
    { 6, 1, 63 },
    { 5, 4, 81 },
    { 10, 5, 44 }
};


/* this function malloc's. up to caller to free */
stock_ret_s *BigMargin(const int *prices, size_t len)
{
    int profit = 0;
    size_t i_buy = 0;
    size_t i_sell = 0;

    stock_ret_s *res = (stock_ret_s*)malloc(sizeof(stock_ret_s));

    if(!res)
    {
        printf("BigMargin failed to allocate %lu bytes!", sizeof(stock_ret_s));
        return NULL;
    }
/* this is purely to prevent valgrind errors */
    res->buy = 0; res->sell = 0; res->margin = 0;

    for(i_sell = 0; i_sell < len; ++i_sell)
    {
        profit = prices[i_sell] - prices[i_buy];

        if(profit > res->margin)
        {
            res->margin = profit;
            res->sell = i_sell;
            res->buy = i_buy;
        }

        if (prices[i_sell] < prices[i_buy])
        {
            i_buy = i_sell;
        }
    }

    return res;
}

int main(void)
{
    stock_ret_s *run = NULL;
    size_t i = 0;


    for(i = 0; i < ARR_LEN(tests); ++i)
    {

        run = BigMargin(tests[i], 11);

        if(run->sell != ex_res[i].sell)
        {
            printf("sell index is wrong!%d %d\n", run->sell, ex_res[i].sell);
        }

        if(run->buy != ex_res[i].buy)
        {
            printf("buy index is wrong!%d %d\n", run->buy, ex_res[i].buy);
        }

        if(run->margin != ex_res[i].margin)
        {
            printf("margin index is wrong!%d %d\n", run->margin, ex_res[i].margin);
        }

        free(run);
    }

    return 0;
}
