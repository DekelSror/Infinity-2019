/*==============================================================================
Data Structures - Bit Array
Header
Dekel Sror
Review - Jenia Taranov
RC 2
==============================================================================*/

#ifndef BIT_ARRAY_HHH
#define BIT_ARRAY_HHH

/* indices start at 0 */
/* defined for indices 0 - 63 */
#include <stddef.h> /* size_t */
#include <limits.h> /* ULONG_MAX */

/* these are being used by both the module and the test file */
#define MASK_1  (0x5555555555555555)
#define MASK_2  (0x3333333333333333)
#define MASK_4  (0x0f0f0f0f0f0f0f0f)

/* set all bits in arr to 1*/
size_t BitArrayAllOn(size_t arr);

/* set all bits in arr to 0 */
size_t BitArrayAllOff(size_t arr);

/* set index bit in arr to 1 */
size_t BitArraySetOn(size_t arr,size_t index);

/* set index bit in arr to 0 */
size_t BitArraySetOff(size_t arr,size_t index);

/* set index bit in arr to value */
size_t BitArraySetBit(size_t arr,size_t index,int value);

/* is index bit in arr on */
int BitArrayIsOn(size_t arr,size_t index);

/* is index bit in arr off */
int BitArrayIsOff(size_t arr,size_t index);

/* flip index bit in arr */
size_t BitArrayFlipBit(size_t arr, size_t index);

/* rotate bits in array n  left */
size_t BitArrayRotateLeft(size_t arr,size_t n);

/* rotate bits in array n  right */
size_t BitArrayRotateRight(size_t arr,size_t n);

/* mirror the bits in each byte of arr */
size_t BitArrayMirrorBytes(size_t arr);

/* mirror the bits in each byte of arr using LUT */
size_t BitArrayMirrorBytesLUT(size_t arr);

/* return num of set bits in arr */
size_t BitArrayCountOn(size_t arr);

/* return num of set bits in arr using LUT */
size_t BitArrayCountOnLUT(size_t arr);

/* return num of unset bits in arr */
size_t BitArrayCountOff(size_t arr);

#endif /* BIT_ARRAY_HHH */
