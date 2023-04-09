#include <stdlib.h> /* malloc, NULL */
#include <ctype.h>	/* tolower */
#include <assert.h>
#include "ilrd_string.h"

/*=======================================================*/
/* WorkSheet 2 exercises 1 - 10 						 */
/* Implement standard string(s).h functions				 */
/* Module												 */
/* Dekel Sror */
/*=======================================================*/

size_t StrLen(const char* str)
{
	const char *current = str;

	assert(str);

    while(*current)
	{
		++current;
	}

    return current - str;
}

int StrCmp(const char *s1, const char *s2)
{
	const char *p1 = s1, *p2 = s2;

	assert(s1);
	assert(s2);

    while(*p1 == *p2)
	{
		if(!*p1)
		{
			break;
		}
		++p1;
		++p2;
	}

    return *p1 - *p2;
}

/* up to caller to have large enough dest buffer */
/* including the terminating byte */

char *StrCpy(char *dest, const char *src)
{
	char *dest_scan = dest;
	const char *src_scan = src;

	assert(dest);
	assert(src);

	while(*src_scan)
	{
		*dest_scan = *src_scan;
		++dest_scan;
		++src_scan;
	}

	*dest_scan = '\0';

	return dest;
}

char *StrnCpy(char *dest, const char *src, size_t n)
{
	char *dest_head = dest;
	size_t i = 0;

	assert(dest); assert(src);

	for(i = 0; i < n; ++i)
	{
		if(!*src)/* n is too big */
		{
			break;
		}
		*dest = *src;
		++dest;
		++src;
	}
	/* if any, pad remaining bytes with zeros */
	for(; i < n; ++i)
	{
		*dest = '\0';
		++dest;
	}

	*dest = '\0';
	dest = dest_head;

	return dest;
}

/* WARNING: up to caller to free allocated memory */
char *StrDup(const char *str)
{
	size_t bytes = StrLen(str) + 1;
	char *buffer = malloc(bytes);

	assert(str);

	if(!buffer)
	{
		return NULL;
	}

	buffer = StrnCpy(buffer, str, bytes);

	return buffer;
}

int StrCaseCmp(const char *s1, const char *s2)
{
    const char *ps1 = s1, *ps2 = s2;

	assert(s1); assert(s2);

    while(tolower(*ps1) == tolower(*ps2))
    {
		if(!*ps1)
		{
			break;
		}

        ++ps1;
        ++ps2;
    }

	return tolower(*ps1) - tolower(*ps2);
}

int StrnCaseCmp(const char *s1, const char *s2, const size_t n)
{
	const char *ps1 = s1, *ps2 = s2;
    size_t i = 1;

	assert(s1); assert(s2);

    if(0 == n)
    {
        return 0;
    }

	while(tolower(*ps1) == tolower(*ps2))
	{
		if(!*ps1 || i == n)
			break;
		++ps1;
		++ps2;
		++i;
	}

	return tolower(*ps1) - tolower(*ps2);
}

/*here as well, up to caller to have big enough buffer*/

char *StrCat(char *dest, const char *src)
{
    char *dest_head = dest;
    size_t dest_len = StrLen(dest);

	assert(dest); assert(src);

    dest += dest_len;
    dest = StrCpy(dest, src);
	dest = dest_head;

    return dest;
}

char *StrnCat(char *dest, const char *src, size_t n)
{
    size_t dest_len = StrLen(dest);
    char *dest_head = dest;

	assert(dest); assert(src);

    dest += dest_len;
    dest = StrnCpy(dest, src, n);
	dest = dest_head;

    return dest;
}


char *StrChr(const char *str, const char c)
{
	const char *ps = str;

	int found = 0;
	size_t steps = 0;
	size_t range = StrLen(str) + 1;

	assert(str);

	while(steps < range)
	{
		if(*ps == c)
		{
			found = 1;
			break;
		}
		++ps;
		++steps;
	}

	return found ? (char*)ps : NULL;
}

size_t StrSpn(const char *str, const char *set)
{
    const char *ps = str;
    size_t seg_len = 0;

	assert(str); assert(set);

	if(!*ps)
	{
		return 0;
	}

    while(StrChr(set, *ps))
    {
		if(!*ps)
		{
			break;
		}
        ++seg_len;
        ++ps;
    }

    return seg_len;
}


char *StrStr(const char *area, const char *target)
{
    const char *pa = area, *pt = target, *hold = NULL;
	size_t i = 0, chunk = 0;

	assert(area); assert(target);

	if(!*pt)
	{
		return (char*)area;
	}

	for(i = 0; i < StrLen(area); ++i)
	{
		if(*pa == *pt)
		{
			hold = pa;
			while(*pt && (*pa == *pt))
			{
				++chunk;
				++pa;
				++pt;
			}
			if(!*pt)
			{
				return (char*)hold;
			}
			else
			{
				i -= chunk + 1;
				pt = target;
			}

		}
		else
		{
			++pa;
		}
	}

	return NULL;
}


char *StrTok(char *str, const char *delim)
{
	static char *to_parse = NULL;
	char *tok_head = NULL;

	if(str)
	{
		to_parse = str;
	}

	while(StrChr(delim, *to_parse))
	{
		if(!*to_parse)
		{
			return NULL;
		}
		++to_parse;
	}

	tok_head = to_parse;

	while(NULL == StrChr(delim, *to_parse))
	{
		if(!*to_parse)
		{
			return tok_head;
		}
		++to_parse;
	}
	*to_parse = 0;
	++to_parse;

	return tok_head;
}
