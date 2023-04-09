#include "ilrd_string.h" /* StrLen */
#include <stdio.h> /* printf */

/*======================================*/
/* WorkSheet 2 exercises 11 - 13        */
/* 1. Check if a string is a palindrome */
/* 2. Seven Boom */
/* 3. Swap to pointers to integers      */
/* Dekel Sror */
/*======================================*/

int IsPali(const char *str);
void Seven_Boom(const size_t range);
void IpSwap(int **pa, int **pb);

int main(void)
{
    int *ipa = NULL, *ipb = NULL;
    int a = 6, b = 7;
    ipa = &a; ipb = &b;
    printf("%d\n", IsPali("abbdbba"));
    printf("%d\n", IsPali("abba"));
    printf("%d\n", IsPali("abdbba"));
    Seven_Boom(50);
    return 0;
}


int IsPali(const char *str)
{
    size_t len = StrLen(str), i = 0;
    const char *start = str, *end = str + len - 1;
    while(*start == *end)
    {
        ++i;
        if(i >= len/2)
            return 1;
        ++start;
        --end;
    }
    return 0;
}

void Seven_Boom(const size_t range)
{
    size_t i = 0;
    size_t tmp = 0;
    int boom = 0;
    for(i = 1; i <= range; ++i)
    {
        boom = 0;
        if(i % 7 == 0)
        {
            boom = 1;
        }
        else
        {
            tmp = i;
            while(tmp)
            {
                if(tmp % 10 == 7)
                {
                    boom = 1;
                    break;
                }
                tmp /= 10;
            }
        }
        if(boom)
        {
            printf("BOOM, ");
        }
        else
        {
            printf("%d, ", i);
        }
    }
}

void IpSwap(int **pa, int **pb)
{
    int *tmp = *pa;
    *pa = *pb;
    *pb = tmp;
}
