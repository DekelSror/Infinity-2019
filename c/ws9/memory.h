
/*========================================================================*/
/* WorkSheet 9 exercise 1                                                 */
/* mem set, cpy, move implementation                                      */
/* Dekel Sror */
/* Review - Yakov Gorochovski                                             */
/*========================================================================*/

#ifndef __MEMORY_H
#define  __MEMORY_H

#define WORD_BYTES (sizeof(size_t))

void *Memset    (void *, int, size_t);
void *Memcpy    (void *, const void *, size_t);
void *Memmove   (void *, const void *, size_t);
void MemPrintArr(void *, size_t);

#endif /* __MEMORY_H */
