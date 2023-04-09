#include <stdio.h> /* printf */
#include <stdlib.h> /*  */
#include <assert.h> /* assert */
#include "bitwise.h"

/*========================================================================*/
/* WorkSheet 6 exercises 1 - 12                                           */
/* Bitwise operations                                                     */
/* Implementations                                                        */
/* Dekel Sror */
/*========================================================================*/



long Pow2(unsigned int x, unsigned int y)
{
    long xl = 0l +(long)x;

    if ((xl << y) < xl)
    {
        return -1l;
    }

    return (xl << y);
}

int IsExactExpOf2Loop(unsigned int n)
{
    unsigned int mask = 0x00000001u;

    if (!n)
    {
        return 0;
    }

    while ((mask <= n) && (mask != 0))
    {
        if (mask == n)
        {
            return 1;
        }
        mask = mask << 1;
    }

    return 0;
}

int IsExactExpOf2(unsigned int n)
{
    return n && 0 == (n & (n-1));
}

void BitwiseIncrement(unsigned int *p)
{
    unsigned int mask = 1u;

    assert(p);

    while (mask & *p)
    {
        *p ^= mask;
        mask <<= 1;
    }

    *p ^= mask;
}

void AreExactly3BitsSet(const unsigned int *uarr, size_t len)
{
    size_t bit_count = 0, i = 0;
    unsigned int mask = 0;

    for (i = 0; i < len; ++i)
    {
        bit_count = 0x00000000u;
        mask  = 0x00000001u;

        while (mask <= uarr[i] && mask)
        {

            if (3lu < bit_count)
            {
                break;
            }

            if (mask & uarr[i])
            {
                ++bit_count;
            }

            mask = mask << 1;
        }

        if (3lu == bit_count)
        {
            printf("0x%x (index %lu) has three set bits\n", uarr[i], i);
        }
    }

    printf("\n\n");
}

int AreBitsTwoAndSixSet(unsigned char x)
{
    return ((0x02 & x) && (0x20 & x));
}

int AreBitsTwoOrSixSet(unsigned char x)
{
    return (x & 0x22);
}

unsigned int FloorToSixTeen(unsigned int n)
{
    return ((n >> 4) << 4);
}


unsigned int CountSetBitsLoop(int n)
{
    unsigned int un = n;
    unsigned int mask = 1u;
    unsigned int count = 0;

    while (mask && (mask <= un))
    {
        if (un & mask)
        {
            ++count;
        }
        mask = mask << 1;
    }

    return count;
}

/* NOT MY ALGORITHM!! refer to README for details */
unsigned int CountSetBits(int n)
{
    unsigned int un = n;

    un = un - ((un >> 1) & 0x55555555u);
    un = (un & 0x33333333u) + ((un >> 2) & 0x33333333u);

    return ((((un + (un >> 4)) & 0x0f0f0f0fu) * 0x01010101u ) >> 24);
}

/* could be generelized with arguments (bit=3, distance=2) */
unsigned char SwapBitThreeWithFive(unsigned char c)
{
    const unsigned char swap_mask = ((c & 0x10) >> 2) + ((c&0x04) << 2);

    return (c & 0xeb) + swap_mask;  /* 1110 1011 */
}

unsigned char ByteMirrorLoop(unsigned char c)
{
    unsigned char mirror = 0x00u;
    size_t i = 0;

    for (i = 0; i < BITS_IN_BYTE; ++i)
    {
        mirror += (c >> (7 - i) & 1) << (i);
    }

    return mirror;
}

unsigned char ByteMirror(unsigned char c)
{
    const unsigned char mask_1 = 0x55u; /*0b 0101 0101 */
    const unsigned char mask_2 = 0x33u; /*0b 0011 0011 */
    const unsigned char mask_4 = 0x0fu; /*0b 0000 1111 */

    c = ((c >> 1) & mask_1) | ((c & mask_1) << 1);
    c = ((c >> 2) & mask_2) | ((c & mask_2) << 2);
    c = ((c >> 4) & mask_4) | ((c & mask_4) << 4);

    return c;
}

unsigned char ByteMirrorAlternate(unsigned char c)
{
/* just to demonstrate */
    const unsigned char mask_1 = 0xaau; /*0b 1010 1010 */
    const unsigned char mask_2 = 0xccu; /*0b 1100 1100 */
    const unsigned char mask_4 = 0xf0u; /*0b 1111 0000 */

    c = ((c << 1) & mask_1) | ((c & mask_1) >> 1);
    c = ((c << 2) & mask_2) | ((c & mask_2) >> 2);
    c = ((c << 4) & mask_4) | ((c & mask_4) >> 4);

    return c;
}

/* prerequisits for swaps - no memory overlap between variables */
/* in many cases this is not faster, since operations depend on previous results */
void XorSwap(unsigned char *c1, unsigned char *c2)
{
/* condition avoids a XOR destruction (a^a = 0) */
    assert(c1);
    assert(c2);

    if(*c1 != *c2)
    {
        *c1 = *c1 ^ *c2;
        *c2 = *c1 ^ *c2;
        *c1 = *c1 ^ *c2;
    }
}

void ArithmeticSwap(unsigned char *c1, unsigned char *c2)
{
    assert(c1);
    assert(c2);

    *c1 = *c1 + *c2;
    *c2 = *c1 - *c2;
    *c1 = *c1 - *c2;
}

void PrintFloat(float *f)
{
    unsigned int *x = (unsigned int *)f;
/* set mask at highest bit - assumes big endian */
    unsigned int mask = 0x80000000;
    size_t i = 0;

    printf("\n\t");
    for (i = 0; i < BITS_IN_BYTE * BYTES_IN_INT; ++i)
    {
        if (0 == i % 4)
        {
            printf(" ");
        }
        printf("%d", (*x & mask) >> (31 - i));
        mask = mask >> 1;
    }

    printf("\n\n");
}
