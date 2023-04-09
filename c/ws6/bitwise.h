



/*========================================================================*/
/* WorkSheet 6 exercises 1 - 12                                           */
/* Bitwise operations                                                     */
/* Header                                                                 */
/* Dekel Sror */
/* Review - Nadav Aharon                                                  */
/*========================================================================*/


#ifndef __BITWISE_H
#define __BITWISE_H

#include <stddef.h> /* size_t  */

#define BITS_IN_BYTE (8)
#define BYTES_IN_INT (4)

#define ARR_LEN(x) (sizeof(x) / sizeof(x[0]))

long          Pow2            (unsigned int, unsigned int);

int             IsExactExpOf2Loop    (unsigned int);
int             IsExactExpOf2        (unsigned int);
int             AreBitsTwoOrSixSet   (unsigned char);
int             AreBitsTwoAndSixSet  (unsigned char);

unsigned int    FloorToSixTeen       (unsigned int);
unsigned int    CountSetBitsLoop     (int);
unsigned int    CountSetBits         (int);

unsigned char   SwapBitThreeWithFive (unsigned char);
unsigned char   ByteMirrorLoop       (unsigned char);
unsigned char   ByteMirror           (unsigned char);
unsigned char   ByteMirrorAlternate  (unsigned char);

void            BitwiseIncrement     (unsigned int *);
void            AreExactly3BitsSet   (const unsigned int *, size_t);
void            XorSwap              (unsigned char *, unsigned char *);
void            ArithmeticSwap       (unsigned char *, unsigned char *);
void            PrintFloat           (float *);

#endif /* __BITWISE_H */
