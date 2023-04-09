
/*========================================================================*/
/* WorkSheet 9 exercise 1                                                 */
/* mem set, cpy, move implementation                                      */
/* Dekel Sror */
/* Review - Yakov Gorochovski                                             */
/*========================================================================*/

#include <stdlib.h>  /* NULL, size_t */
#include <stdio.h> /* printf for MemPrintArr */
#include <assert.h>

#include "memory.h"

void *Memset(void *s, int c, size_t n)
{
	size_t words = 0;
	size_t rem_bytes = 0;
	size_t word_mask = 0;
	size_t i = 0;
	size_t *bulk_write = NULL;
	char   *byte_write = NULL;

	assert(s);

	byte_write = (char*)s;

/* write byte-by-byte until point to aligned address */
	while ((0 != (unsigned long)byte_write % WORD_BYTES) && n)
	{
		*byte_write = (c & 0xff);
		++byte_write;
		--n;
	}

/* write words as long as possible */
	words = n / WORD_BYTES;
	rem_bytes = n % WORD_BYTES;
	bulk_write = (size_t *)byte_write;

	for (i = 0; i < WORD_BYTES; ++i)
	{
		word_mask <<= 8;
		word_mask += (c & 0xff);
	}

/* write byte-by-byte until end */
	for (i = 0; i < words;  ++i)
	{
		*bulk_write = word_mask;
		++bulk_write;
	}

	byte_write = (char*)bulk_write;

	for (i = 0; i < rem_bytes; ++i)
	{
		*byte_write = (c & 0xff);
		++byte_write;
	}

	return s;
}

void *Memcpy(void *dest, const void *src, size_t n)
{
	size_t *bulk_write = NULL;
	size_t i = 0;
	size_t words = 0;
	size_t rem_bytes = 0;

	char *src_ptr = NULL;
	char *byte_write = NULL;

	assert(dest);
	assert(src);

	src_ptr = (char *)src;
	byte_write = (char *)dest;

	while (0 != ((size_t)byte_write % WORD_BYTES) && n)
	{
		*byte_write = *(char *)src_ptr;
		--n;
		++src_ptr;
		++byte_write;

	}

	bulk_write = (size_t *)byte_write;

	words = n / WORD_BYTES;
	rem_bytes = n % WORD_BYTES;

	for (i = 0; i < words; ++i)
	{
		*bulk_write = *(size_t *)src_ptr;
		src_ptr += WORD_BYTES;
		++bulk_write;
	}

	byte_write = (char *)bulk_write;

	for (i = 0; i < rem_bytes; ++i)
	{
		*byte_write = *(char *)src_ptr;
		++byte_write;
		++src_ptr;
	}

	return dest;
}

void *Memmove(void *dest, const void *src, size_t n)
{
	size_t *bulk_write = NULL;
	size_t i = 0;
	size_t words = 0;
	size_t rem_bytes = 0;

	char *src_ptr = NULL;
	char *byte_write = NULL;

	assert(dest);
	assert(src);

	if (dest <= src)
	{
		return Memcpy(dest, src, n);
	}

	src_ptr = (char *)src + n;
	byte_write = (char *)dest + n;

	while (0 != ((size_t)byte_write % WORD_BYTES) && n)
	{
		--src_ptr;
		--byte_write;
		*byte_write = *(char *)src_ptr;
		--n;

	}

	bulk_write = (size_t *)byte_write;

	words = n / WORD_BYTES;
	rem_bytes = n % WORD_BYTES;

	for (i = 0; i < words; ++i)
	{
		--bulk_write;
		*bulk_write = *(size_t *)src_ptr;
		src_ptr -= WORD_BYTES;
	}

	byte_write = (char *)bulk_write;

	for (i = 0; i < rem_bytes; ++i)
	{
		--byte_write;
		--src_ptr;
		*byte_write = *(char *)src_ptr;
	}

	return dest;
}

/* this isn't called but was EXTREMELY useful while debugging */
void MemPrintArr(void *arr, size_t words)
{
	size_t i = 0;
	size_t *arr_print = NULL;

	assert(arr);

	arr_print = (size_t *)arr;

	for (i = 0; i < words; ++i)
	{
		printf("%16.lx,\t\t",*(arr_print + i));
		if (0 == (i + 1) % 4)
		{
			printf("\n");
		}
	}

	printf("\n");
}
