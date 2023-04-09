#/*=============================================================================
# Recursion
# Test
# Dekel Sror
# Review - Tzvi cubac
# RC 1
#=============================================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "recursion.h"

int SortTest(void);

int main(void)
{
	char *buff_5 = malloc(5);
	char *buff_a = malloc(0xa);

	size_t i = 0;
	int arr[] = { 0,1,2,3,4,5,6,7,8,9 };

	node_t *test_head = ListCreateNode(&arr[0], NULL);
	node_t *runner = test_head;

	for (i = 1; i < 10; ++i)
	{
		ListInsertAfter(ListCreateNode(&arr[i], NULL), runner);
		runner = runner->next;
	}


	printf("rec_fib 6: %lu\n", RecFibo(6));
	printf("iterative_fib 6: %lu\n", RecFibo(6));
	printf("rec_fib 9: %lu\n", RecFibo(9));
	printf("iterative_fib 9: %lu\n", RecFibo(9));
	printf("rec_fib 1: %lu\n", RecFibo(1));
	printf("iterative_fib 1: %lu\n", RecFibo(1));
	printf("rec_fib 0: %lu\n", RecFibo(0));
	printf("iterative_fib 0: %lu\n", RecFibo(0));

	printf("len papa: %lu\n", StrLen("papa"));
	printf("len [empty]: %lu\n", StrLen(""));

	printf("good comp (0) : %d\n", StrCmp("abba", "abba"));
	printf("bad  comp (-1): %d\n", StrCmp("abba", "abca"));

	buff_5 = StrCpy(buff_5, "abba");

	printf("cpy [abba] : %s\n", buff_5);

	buff_a = StrCpy(buff_a, "papa");
	buff_a = StrCat(buff_a, "-mama");

	printf("cat [papa],[-mama]: %s\n", buff_a);

	buff_5 = StrCpy(buff_5, "-m");

	printf("Str [-m] :%s\n", StrStr(buff_a, buff_5));

	buff_5 = StrCpy(buff_5, "--");
	printf("Str [--] :%s\n", StrStr(buff_a, buff_5));

	buff_a = StrCpy(buff_a, "-a-m-p-m");
	printf("Str [--] :%s\n", StrStr(buff_a, buff_5));


	ListPrint(test_head);

	test_head = Flip(test_head);

	ListPrint(test_head);

	free(buff_5);
	free(buff_a);
	ListFreeAll(test_head);

	printf("StackSort 512 ints: %d errors\n", SortTest());

	return 0;
}



int SortTest(void)
{
	istack_t *test = IntStackCreate(0x200);
	int errs = 0;

	srand(getpid());


	while (0x200 > IntStackSize(test))
	{
		IntStackPush(test, rand());
	}

	printf("full: %lu\n", IntStackSize(test));

	StackSort(test);

	while (1 < IntStackSize(test))
	{
		int check = IntStackPeek(test);

		IntStackPop(test);

		if (IntStackPeek(test) < check)
		{
			++errs;
		}
	}

	IntStackDestroy(test);

	return errs;
}
