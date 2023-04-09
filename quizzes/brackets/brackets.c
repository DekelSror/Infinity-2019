#include <stdio.h>
#include <string.h>

#include "stack.h"

#define OPENERS ("{[(")
#define CLOSERS ("}])")

#define LUT_SIZE (256)

void MakeLUT(size_t *table, int *flag);
int BracketValidator(const char *str);
int IsMatch(char closer, char opener);


int main(void)
{
    char *t1 = "(({{()}})){{}}";
    char *t2 = "}";
    char *t3 = "({)}";

    printf("for t1: %d\n", BracketValidator(t1));
    printf("for t2: %d\n", BracketValidator(t2));
    printf("for t3: %d\n", BracketValidator(t3));

    return 0;
}


int BracketValidator(const char *str)
{
    const char *p = str;
    size_t len = strlen(str);
    size_t valid = 0;
    stack_t *stack = StackCreate(sizeof(char), len);

    while ('\0' != *p)
    {
        if (strchr(OPENERS, *p))
        {
            StackPush(stack, p);
        }
        else
        {
            if (0 == StackSize(stack) || !IsMatch(*p, *(char *)StackPeek(stack)))
            {
                StackDestroy(stack);

                return 0;
            }
            else
            {
                StackPop(stack);
            }
        }

        ++p;
    }

    valid = StackSize(stack);
    StackDestroy(stack);

    return (0 == valid);
}

int IsMatch(char closer, char opener)
{
    static size_t lut[LUT_SIZE] = { 0 };
    static int generated = 0;

    if (!generated)
    {
        MakeLUT(lut, &generated);
    }

    return (lut[opener] == lut[closer]);
}

void MakeLUT(size_t *table, int *flag)
{
    size_t i = 0;

    for (i = 0; i < 2; ++i)
    {
        char *p = ((0 == (i % 2)) ? OPENERS : CLOSERS);
        size_t spot = 1;

        while ('\0' != *p)
        {
            table[*p] = spot;
            ++spot;
            ++p;
        }
    }

    *flag = 1;
}
