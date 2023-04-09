/*==============================================================================
Quiz - Int Stack - wrapper on stack
Tests
Dekel Sror
Version 1
==============================================================================*/
#include <stdio.h>

#include "istack.h"

#define NUM_TESTS (9)

int main(void)
{
    size_t passed_tests = 0;
    istack_t *test = IntStackCreate(5);

    IntStackPush(test, 8);
    passed_tests += (IntStackPeek(test) == 8);
    IntStackPush(test, 5);
    passed_tests += (IntStackPeek(test) == 5);
    IntStackPush(test, 9);
    passed_tests += (IntStackPeek(test) == 9);

    passed_tests += (InststackSize(test) == 3);

    IntStackPop(test);
    passed_tests += (IntStackPeek(test) == 5);
    passed_tests += (InststackSize(test) == 2);

    IntStackPop(test);
    passed_tests += (IntStackPeek(test) == 8);
    passed_tests += (InststackSize(test) == 1);

    IntStackPop(test);
    passed_tests += (InststackSize(test) == 0);

    IntStackDestroy(test);

    printf("passed_tests: %lu out of %d\n", passed_tests, NUM_TESTS);

    return 0;
}
