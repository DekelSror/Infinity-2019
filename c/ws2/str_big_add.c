#include <stdlib.h> /* NULL, size_t, malloc, realloc, free */
#include <stdio.h> /* printf */
#include <assert.h>
#include "ilrd_string.h" /* StrLen, StrCpy */

/*=============================================*/
/* WorkSheet 2 exercise 14                     */
/* add very large positive integers as strings */
/* return result as string                     */
/* Dekel Sror */
/*=============================================*/

/* TODO: write proper tests */

char *ChrAdd(const char d1, const char d2);
char *StrBigAdd(const char *s1, const char *s2);

int main(void)
{
    const char *n1 = "9";
    const char *n2 = "995";
    char *test = NULL;

    test = StrBigAdd(n1, n2);
    printf(" %s\n+\n %s\n=\n %s\n\n\n", n1, n2, test);
    free(test);

    return 0;
}

/* functons assume strings are all numeric ASCII values, decimal base numbers */
char *ChrAdd(const char d1, const char d2)
{
    char mod = (d1+d2-96) % 10;
    char carry = (d1+d2-96) / 10;
    char *res = (char*)malloc(2);
    *res = mod;
    *(res + 1) = carry;
    return res;
}

/* caller is responsible to free */
char *StrBigAdd(const char *s1, const char *s2)
{
    char *runner = NULL;
    char *result = NULL, *res_head = NULL, *res_tail = NULL;
    char *long_s = NULL, *long_s_head = NULL, *long_s_tail = NULL;
    char *short_s = NULL, *short_s_head = NULL, *short_s_tail = NULL;
    size_t res_len = 0;

    assert(s1); assert(s2);

    if (StrLen(s1) >= StrLen(s2))
    {
        long_s_head = (char*)s1;
        short_s_head = (char*)s2;
    }

    else
    {
        long_s_head = (char*)s2;
        short_s_head = (char*)s1;
    }

    short_s_tail = short_s_head + StrLen(short_s_head) - 1;
    short_s = short_s_tail;
    long_s_tail = long_s_head + StrLen(long_s_head) - 1;
    long_s = long_s_tail;


/* allocate 1 byte for terminating char, one for possible carry */
    res_len = StrLen(long_s_head) + 1;
    result = (char*)malloc(res_len + 1);

    if (!result)
    {
        return NULL;
    }

    res_head = result;
    *(res_head + res_len) = '\0';
    res_tail = res_head + res_len - 1;

    while (result <= res_tail)
    {
        *result = '0';
        ++result;
    }

    result = res_head;
    result = res_tail;

/* add short to long from the bottom up  */
    while (short_s >= short_s_head)
    {
        runner = ChrAdd(*long_s, *short_s);
        *result += runner[0];
        *(result - 1) += runner[1];
        free(runner);
        --short_s;
        --long_s;
        --result;
    }

/* add remaining long digits with zeros */
    while (long_s >= long_s_head)
    {
        runner = ChrAdd(*long_s, '0');
        *result += runner[0];
        *(result - 1) += runner[1];
        --long_s;
        --result;
        free(runner);
    }

    result = res_head;

/* deal with carry */
    if ('0' == *result)
    {
        StrCpy(result, result + 1);
        result = (char*)realloc(result, res_len);

        if (!result)
        {
            return NULL;
        }
    }

    return result;
}
