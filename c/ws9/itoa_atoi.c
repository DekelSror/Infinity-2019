
/*========================================================================*/
/* WorkSheet 9 exercise 2                                                 */
/* itoa and atoi implementation                                           */
/* Dekel Sror */
/* Review - Yakov Gorochovski                                             */
/*========================================================================*/

#include <stdio.h> /* printf */
#include <stdlib.h> /* NULL, malloc, free */
#include <ctype.h> /* tolower */
#include <string.h> /* strlen, strcmp */
#include <math.h> /* pow */
#include <assert.h>


#define ARR_LEN(x) (sizeof(x) / sizeof(x[0]))

int Atoi    (const char *, unsigned char);
int TestAtoi(const char *, unsigned char, int);

char *Itoa  (int, unsigned char, char *);
int TestItoa(int, unsigned char, char*, const char *);

int main(void)
{
    char *test_arr = (char *)malloc(20);
    size_t successful_tests = 0;

    if (!test_arr)
    {
        printf("malloc failed to allocate 20 bytes!\n");
        return 1;
    }
                    /*         Itoa tests          */

    successful_tests += TestItoa(1, 10, test_arr, "1");
    successful_tests += TestItoa(0, 2, test_arr, "0");
    successful_tests += TestItoa(-1, 10, test_arr, "-1");
    successful_tests += TestItoa(11, 25, test_arr, "b");
    successful_tests += TestItoa(11, 2, test_arr, "1011");
    successful_tests += TestItoa(0x3f0ff0f1, 2, test_arr, "111111000011111111000011110001");

                    /*           Atoi tests          */

    successful_tests += TestAtoi("11", 16, 17);
    successful_tests += TestAtoi("1d", 23, 36);
    successful_tests += TestAtoi("aaaaa", 15, 542410);
    successful_tests += TestAtoi("0", 20, 0);
    successful_tests += TestAtoi("-1", 14, -1);
    successful_tests += TestAtoi("-1", 10, -1);

    printf("finished testing Itoa / Atoi. %lu successful_tests out of %d\n"
            , successful_tests, 12);

    free(test_arr);
    test_arr = NULL;

    return 0;
}
                        /*          test functions          */

int TestAtoi(const char *str, unsigned char base , int expected)
{
    int res = Atoi(str, base);

    if (res != expected)
    {
        printf("Atoi failed for input %s base %d, output %d, expected %d\n"
                , str, base, res, expected);

        return 0;
    }

    return 1;
}

int TestItoa(int to_parse, unsigned char base, char* buffer, const char *expected)
{
    buffer = Itoa(to_parse, base, buffer);

    if (strcmp(buffer, expected))
    {
        printf("Itoa failed for input 0x%x base %d, output was %s, expected %s\n"
            , to_parse, base , buffer, expected);

        return 0;
    }

    return 1;
}

                        /*          implementations             */


char *Itoa(int to_parse, unsigned char base, char *s)
{
    int val_save = 0;
    size_t chars = 0;
    unsigned char mod = 0;
    int is_nega = 0;

    assert(s);

/* explicitly check for zero as it sneaks through */
    if (0 == to_parse)
    {
        *s = '0';
        *(s+1) = 0;
        return s;
    }
/* check for negative values - non decimal assumed unsigned */
    if (0 > to_parse && base == 10)
    {
        to_parse *= -1;
        is_nega = 1;
    }

    val_save = to_parse;

/* count digits */
    while (to_parse)
    {
        ++chars;
        to_parse /= base;
    }

/* terminate string */
    s += chars + is_nega;
    *s = 0;

/* convert to ASCII and write */
    while (val_save)
    {
        --s;
        mod = val_save % base;
/* if mod > 9, make a lowercase letter out of it. else, make it it's corresponding ASCII digit */
        *s = (mod > 9) ? (mod + 87) : (mod + 48);
        val_save /= base;
    }

    if (is_nega)
    {
        --s;
        *s = '-';
    }

    return s;
}

/* handles alpha-numeric values only */
int Atoi(const char *s, unsigned char base)
{
    size_t i = 0;
    size_t len = 0;
    unsigned char digit = 0;
    unsigned char exp = 0;
    int is_nega = 0;
    int res = 0;

    assert(s);
    len = strlen(s);

    if ('-' == *s)
    {
        is_nega = 1;
    }

    s += len - (1);

    for (i = 0; i < (len - is_nega); ++i)
    {

        if (!(isalnum(*s)))
        {
            printf("Atoi says : invalid input string!! \n");
            return 0;
        }

        /*'7' => 55 - 48 = 7 ... 'A' => 'a' => 97 - 48 = 49 */
        digit = tolower((unsigned char)*s) - 48;

        if (9 < digit)
        {
            digit -= 39; /* 49 - 39 = 10 => 'a' */
        }

        res += digit * pow(base, exp);
        ++exp;
        --s;
    }

    if (is_nega)
    {
        res *= -1;
    }

    return res;
}
