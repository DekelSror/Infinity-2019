/*==============================================================================
Quiz - Int Stack - wrapper on stack
Module
Dekel Sror
Version 1
==============================================================================*/
#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert       */

#include "stack.h"
#include "istack.h"

struct istack_s
{
    stack_t *stack;
};

istack_t *IntStackCreate(size_t num_of_elems)
{
    istack_t *new_st = (istack_t *)malloc(sizeof(istack_t));

    new_st->stack = StackCreate(sizeof(int), num_of_elems);

    if (NULL == new_st->stack)
    {
        return NULL;
    }

    return new_st;
}

void IntStackDestroy(istack_t *st)
{
    assert(st);

    StackDestroy(st->stack);

    free(st);

    st = NULL;
}

void IntStackPush(istack_t *st, int num)
{
    assert(st);

    StackPush(st->stack, &num);
}

void IntStackPop(istack_t *st)
{
    assert(st);

    StackPop(st->stack);
}

int IntStackPeek(istack_t *st)
{
    assert(st);

    return *(int *)StackPeek(st->stack);
}

size_t IntStackSize(const istack_t *st)
{
    assert(st);

    return StackSize(st->stack);
}
