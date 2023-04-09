/*==============================================================================
Data Structures - Bit Array
Module
Dekel Sror
Review - Jenia Taranov
RC 2
==============================================================================*/

#include <assert.h>
#include "bitarray.h"

#define UNUSED(x) (void)(x)
#define WORD_BYTES   (sizeof(size_t))
#define BITS_IN_BYTE (8)
#define WORD_BITS    (size_t)(WORD_BYTES * BITS_IN_BYTE)
#define BYTE_RANGE (256)

/* macros for the count_lut generation */
#define COUNT_TWO_BITS(n) (n), (n+1), (n+1), (n+2)

#define COUNT_NIBBLE(n)   COUNT_TWO_BITS(n), COUNT_TWO_BITS(n+1)\
                         ,COUNT_TWO_BITS(n+1), COUNT_TWO_BITS(n+2)

#define COUNT_BYTE(n)   COUNT_NIBBLE(n), COUNT_NIBBLE(n+1)\
                       ,COUNT_NIBBLE(n+1), COUNT_NIBBLE(n+2)

static const size_t count_lut[BYTE_RANGE] =
{

    COUNT_BYTE(0), COUNT_BYTE(1), COUNT_BYTE(1), COUNT_BYTE(2)
};

size_t BitArrayAllOn(size_t arr)
{
    UNUSED(arr);
    return ULONG_MAX;
}

size_t BitArrayAllOff(size_t arr)
{
    UNUSED(arr);
    return (size_t)0;
}

size_t BitArraySetOn(size_t arr,size_t index)
{
    assert(index < WORD_BITS);

    return arr | ((size_t)1 << index);
}

size_t BitArraySetOff(size_t arr,size_t index)
{
    assert(index < WORD_BITS);

    return arr & ~((size_t)1 << index);
}

size_t BitArraySetBit(size_t arr,size_t index,int value)
{
    assert(index < WORD_BITS);

    if (value)
    {
        return BitArraySetOn(arr, index);
    }

    return BitArraySetOff(arr, index);
}

int BitArrayIsOn(size_t arr,size_t index)
{
    assert(index < WORD_BITS);

    return ((arr & ((size_t)1 << index)) >> index);
}

int BitArrayIsOff(size_t arr,size_t index)
{
    assert(index < WORD_BITS);

    return 1 ^ BitArrayIsOn(arr, index);
}

size_t BitArrayFlipBit(size_t arr, size_t index)
{
    assert(index < WORD_BITS);

    return (arr ^ ((size_t)1 << index));
}

size_t BitArrayRotateLeft(size_t arr,size_t n)
{
    return ((arr << n) | (arr >> (WORD_BITS - n)));
}

size_t BitArrayRotateRight(size_t arr,size_t n)
{
    return ((arr >> n) | (arr << (WORD_BITS - n)));
}

size_t BitArrayMirrorBytes(size_t arr)
{
    arr =  ((arr >> 1) & MASK_1) | ((arr & MASK_1) << 1);
    arr =  ((arr >> 2) & MASK_2) | ((arr & MASK_2) << 2);

    return ((arr >> 4) & MASK_4) | ((arr & MASK_4) << 4);
}

size_t BitArrayCountOn(size_t arr)
{
    size_t count = 0;

    while(arr)
    {
        arr &= arr - (size_t)1;
        ++count;
    }

    return count;
}

size_t BitArrayCountOff(size_t arr)
{
    return BitArrayCountOn(~arr);
}

size_t BitArrayCountOnLUT(size_t arr)
{
    size_t i = 0;
    size_t count = 0;

    for (i = 0; i < WORD_BYTES; ++i)
    {
        count += count_lut[0xff & (arr >> (BITS_IN_BYTE * i))];
    }

    return count;
}

static void GenerateMirrorLut(size_t *lut)
{
    size_t i = 0;

    for (i = 0; i < BYTE_RANGE; ++i)
    {
        lut[i] = BitArrayMirrorBytes(i);
    }
}

size_t BitArrayMirrorBytesLUT(size_t arr)
{
    static int generated_flag = 0;
    static size_t mirror_lut[BYTE_RANGE] = { 0 };
    size_t i = 0;
    size_t res = 0;

    if (0 == generated_flag)
    {
        GenerateMirrorLut(mirror_lut);
        generated_flag = 1;
    }

    for (i = 0; i < WORD_BYTES; ++i)
    {
        res += mirror_lut[0xff & (arr)] << (BITS_IN_BYTE * i);
        arr >>= BITS_IN_BYTE;
    }

    return res;
}
