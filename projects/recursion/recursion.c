#/*=============================================================================
# Recursion
# Module
# Dekel Sror
# Review - Tzvi cubac
# RC 1
#=============================================================================*/
#include <stddef.h> /* size_t */

#include "recursion.h"

node_t *Flip(node_t *list)
{
	node_t *node = list;

	if (NULL == list->next)
	{
		goto ret;
	}

	node = Flip(list->next);

	list->next->next = list;
	list->next = NULL;

	ret:
		return node;
}

size_t RegFibo(size_t n)
{
    size_t fib_min_1 = 1;
    size_t fib_min_2 = 0;
    size_t result = fib_min_1;

    while (n >= 1)
    {
        result = fib_min_1 + fib_min_2;
        fib_min_2 = fib_min_1;
        fib_min_1 = result;
        --n;
    }

    return result;
}


size_t RecFibo(size_t n)
{
	if (1 >= n)
	{
		return 1;
	}

	return (RecFibo(n - 1) + RecFibo(n - 2));
}

size_t StrLen(const char *s)
{
	if ('\0' == *s)
	{
		return 0;
	}

	return (1 + StrLen(s + 1));
}

int StrCmp(const char *s1, const char *s2)
{
	if ((*s1 != *s2) || ('\0' == *s1))
	{
		return *s1 - *s2;
	}

	return StrCmp(s1 + 1, s2 + 1);
}

char *StrCpy(char *dest, const char *src)
{
	if ('\0' == *src)
	{
		*dest = '\0';

		return dest;
	}

	*dest = *src;

	return StrCpy(dest + 1, src + 1) - 1;
}

char *StrCat(char *dest, const char *src)
{
	if ('\0' == *dest)
	{
		return StrCpy(dest, src);
	}

	return StrCat(dest + 1, src) - 1;
}

char *StrStr(const char *haystack, const char *needle)
{
	if ('\0' == *haystack)
	{
		return NULL;
	}

	if ('\0' == *needle)
	{
		return (char *)haystack;
	}

	if (*haystack == *needle)
	{
		char *found = StrStr(haystack + 1, needle + 1) - 1;

		if (haystack == found)
		{
			return (char *)haystack;
		}
	}

	return StrStr(haystack + 1, needle);
}

static int IsStackEmpty(const istack_t *st)
{
	return (0 == IntStackSize(st));
}

static void InsertToSortedStack(istack_t *st, int num)
{
	if ((IsStackEmpty(st)) || (IntStackPeek(st) > num))
	{
		IntStackPush(st, num);

		return;
	}
	else
	{
		int insert_top = IntStackPeek(st);
		IntStackPop(st);
		InsertToSortedStack(st, num);
		IntStackPush(st, insert_top);
	}
}

void StackSort(istack_t *st)
{
	if (IsStackEmpty(st))
	{
		return;
	}
	else
	{
		int sort_top = IntStackPeek(st);
		IntStackPop(st);
		StackSort(st);
		InsertToSortedStack(st, sort_top);
	}
}
