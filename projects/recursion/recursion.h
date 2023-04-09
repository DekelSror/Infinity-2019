#/*=============================================================================
# Recursion
# Header
# Dekel Sror
# Review - Tzvi cubac
# RC 1
#=============================================================================*/
#ifndef RECURSION_HH_
#define RECURSION_HH_

#include "linked_list.h" /* node_t, list API for Flip */
#include "istack.h" /* stack of integers for StackSort, istack_t, stack API */

void StackSort(istack_t *st);

node_t *Flip(node_t *list);

size_t RegFibo(size_t n);

size_t RecFibo(size_t n);

size_t StrLen(const char *s);

int StrCmp(const char *s1, const char *s2);

char *StrCpy(char *dest, const char *src);

char *StrCat(char *dest, const char *src);

char *StrStr(const char *haystack, const char *needle);


#endif /* RECURSION_HH_ */
