/*==============================================================================
Data Structures - Stack
Module
Dekel Sror
Review - Tzvi Cubac
RC 1
==============================================================================*/

#include <stdlib.h> /* malloc, free */
#include <string.h> /* memcpy */
#include <assert.h>

#include "stack.h"

struct stack_t
{
    char *top;
    size_t element_size;
    char data [1];
};

stack_t *StackCreate(size_t element_size, size_t num_of_elements)
{
    stack_t *new_stack = (stack_t*)malloc(sizeof(stack_t) +
                          element_size * (num_of_elements + 1));

    assert(element_size > 0);
    assert(num_of_elements > 0);

    if ((NULL == new_stack) || (element_size <= 0) || (num_of_elements <= 0))
    {
        return NULL;
    }

    new_stack->top = (char*)new_stack->data;
    new_stack->element_size = element_size;

    return new_stack;
}

void StackDestroy(stack_t *st)
{
    assert(st);

    free(st);
    st = NULL;
}

void StackPush(stack_t *st, const void *element)
{
    assert(st);

    st->top += st->element_size;
    memcpy(st->top, element, st->element_size);
}

void StackPop(stack_t *st)
{
    assert(st);

    st->top -= st->element_size;
}

void *StackPeek(stack_t *st)
{
    assert(st);

    return (void*)(st->top);
}

size_t StackSize(const stack_t *st)
{
    assert(st);

    return (st->top - st->data) / st->element_size;
}
