
/*========================================================================*/
/* WorkSheet 9 exercise 1                                                 */
/* mem set, cpy, move implementation                                      */
/* Dekel Sror */
/* Review - Yakov Gorochovski                                             */
/*========================================================================*/

#include <stdio.h> /* printf */
#include <string.h> /* memcpy, memset, memmove, memcmp */

#include "memory.h"

int main(void)
{
	static char test[128] = { 0 };
	static char compare_with[128] = { 0 };
	size_t successful_tests = 0;

			/*			set tests			*/

	Memset((test + 3), 20, 8);
	memset((compare_with + 3), 20, 8);

	if (memcmp(test, compare_with, 128))
	{
		printf("\n\t Memset FAILED after fitsr set\n");
	}

	else
	{
		++successful_tests;
	}

	Memset((test + 6), 41, 65);
	memset((compare_with + 6), 41, 65);

	if (memcmp(test, compare_with, 128))
	{
		printf("\n\t Memset FAILED after second set\n");
	}

	else
	{
		++successful_tests;
	}

			/*			cpt tests			*/

	Memcpy(test + 80, test, 15);
	memcpy(compare_with + 80, compare_with, 15);

	if (memcmp(test, compare_with, 128))
	{
		printf("Memcpy Failed after first test\n");
	}

	else
	{
		++successful_tests;
	}

	Memcpy(test, test + 5, 0);
	memcpy(compare_with, compare_with + 5, 0);

	if (memcmp(test, compare_with, 128))
	{
		printf("Memcpy Failed after second test\n");
	}

	else
	{
		++successful_tests;
	}

			/*			move tests			*/

	Memmove(test + 6, test + 10, 29);
	memmove(compare_with + 6, compare_with + 10, 29);

	if (memcmp(test, compare_with, 128))
	{
		printf("Memmove Failed after second move\n");
	}

	else
	{
		++successful_tests;
	}

	Memmove(test + 10, test, 63);
	memmove(compare_with + 10, compare_with, 63);

	if (memcmp(test, compare_with, 128))
	{
		printf("Memmove Failed after first move\n");
	}

	else
	{
		++successful_tests;
	}

	printf("finished tests with %lu successful_tests out of %d\n"
			, successful_tests, 6);

	return 0;
}
