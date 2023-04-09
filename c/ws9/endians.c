#include <stdio.h>

#define OFFSET(s, f) ((unsigned long)(&((s*)0)->f))

#define IS_LIL_ENDIAN ((char)(int)1 > 0)

struct test
{
    int i;
    char a;
    char b;
    char c;
    short s;
    int *p;
};

int main(void)
{
    unsigned long successful_tests  = 0;

    if (0 != OFFSET(struct test, i))
    {
        printf("failed to OFFSET field %c in 'struct test'\n", 'i');
    }

    else
    {
        ++successful_tests;
    }

    if (4 != OFFSET(struct test, a))
    {
        printf("failed to OFFSET field %c in 'struct test'\n", 'a');
    }

    else
    {
        ++successful_tests;
    }

    if (5 != OFFSET(struct test, b))
    {
        printf("failed to OFFSET field %c in 'struct test'\n", 'b');
    }

    else
    {
        ++successful_tests;
    }

    if (6 != OFFSET(struct test, c))
    {
        printf("failed to OFFSET field %c in 'struct test'\n", 'c');
    }

    else
    {
        ++successful_tests;
    }

    if (8 != OFFSET(struct test, s))
    {
        printf("failed to OFFSET field %c in 'struct test'\n", 's');
    }

    else
    {
        ++successful_tests;
    }

    if (16 != OFFSET(struct test, p))
    {
        printf("failed to OFFSET field %c in 'struct test'\n", 'p');
    }

    else
    {
        ++successful_tests;
    }

    printf("finished tests for OFFSET with %lu out of %u successful_tests\n"
            , successful_tests, 6u);


    printf("IS_LIL_ENDIAN returned %d\n", IS_LIL_ENDIAN);
    return 0;
}
