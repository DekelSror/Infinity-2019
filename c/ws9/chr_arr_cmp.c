
/*========================================================================*/
/* WorkSheet 9 exercise 3                                                 */
/* compare three char arrays                                              */
/* Dekel Sror */
/* Review - Yakov Gorochovski                                             */
/*========================================================================*/

#include <stdio.h>


void ChrArrCmp(const char s1[], const char s2[], const char s3[], size_t len_s1, size_t len_s2, size_t len_s3);

static const char test_s1[] = { 'a', 'b', '+', 'x', '+' };
static const char test_s2[] = { 'b', 'x', '+', 'y' };
static const char test_s3[] = { 'a', 'a', 'b', 'b', 'y', 't', 'f' };

static const char yk_s1[] = { 'a', 'q' };
static const char yk_s2[] = { 'q', 'q' };
static const char yk_s3[] = { 'a', 'f' };

int main(void)
{

    ChrArrCmp(yk_s1, yk_s2, yk_s3, 2, 2, 2); /* expected 'q' */
    ChrArrCmp(yk_s2, yk_s3, yk_s1, 2, 2, 2); /* expected nothing */
    ChrArrCmp(yk_s1, yk_s3, yk_s2, 2, 2, 2); /* expected 'a' */

    ChrArrCmp(test_s1, test_s2, test_s3, 5, 4, 7); /* expected '+' 'x' */
    ChrArrCmp(test_s2, test_s3, test_s1, 4, 7, 5); /* expected 'y' */
    ChrArrCmp(test_s1, test_s3, test_s2, 5, 7, 4); /* expected nothing */

    return 0;
}

void ChrArrCmp(const char s1[], const char s2[], const char s3[], size_t len_s1, size_t len_s2, size_t len_s3)
{
    size_t i = 0;
/* empty buffer 256 bytes, zeroed */
    unsigned char table[256] = { 0 };

/* run through first array. Mark 1 in appropriate spot for each char */
    for (i = 0; i < len_s1; ++i)
    {
        table[(size_t)s1[i]] = 1;
    }
/* run through second array. Mark twos on top of ones */
    for (i = 0; i < len_s2; ++i)
    {
        if (table[(size_t)s2[i]])
        {
            table[(size_t)s2[i]] = 2;
        }
    }
/* run through third array. Mark 0 on top of twos */
    for (i = 0; i < len_s3; ++i)
    {
        if (2 == table[(size_t)s3[i]])
        {
            table[(size_t)s3[i]] = 0;
        }
    }
/* print only ASCII codes that correspond to twos in buffer */
    for (i = 0; i < 256; ++i)
    {
        if ( 2 == table[i])
        {
            printf("'%c', ", (char)i);
        }
    }

    printf("\n\n");
}
