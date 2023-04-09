/*==============================================================================
Data Structures - Stack
Header
Dekel Sror
Review - Tzvi Cubac
RC 1
==============================================================================*/

#ifndef STACK_H_XXX
#define STACK_H_XXX

#include <stddef.h> /* size_t */

typedef struct stack_t stack_t;

/* Create a new stack.

parameters:
      element_size - size of each element in stack.
      num_of_elements - number of elements in stack.

returns pointer to newly created stack.
if element_size or num_of_elements is 0 return NULL.
this is equal to a StackCreate failure (no stack is created). */
stack_t *StackCreate(size_t element_size, size_t num_of_elements);

/* Destroy stack.

parameters:
      st- pointer to stack.

return value is void
if st is NULL no operation is performed */
void StackDestroy(stack_t *st);

/* Push new element to stack.

parameters:
      element - pointer to element data or data itself.
      st- pointer to stack.

return value is void.
if stack is full or st is NULL behaviour is undefined! */
void StackPush(stack_t *st, const void *element);

/*  removes top element from stack.

parameters:
      st- pointer to stack.

return value is void.
if stack is empty or st is NULL behaviour is undefined */
void StackPop(stack_t *st);

/*  returns top element from stack.

parameters:
      st- pointer to stack.

return element in top of stack.
if stack is empty or st is NULL behaviour is undefined */
void *StackPeek(stack_t *st);

/*  returns number of elements in stack
parameters:
      st- pointer to stack.

return value is the number of elements in stack.
if st is NULL behaviour is undefined */
size_t StackSize(const stack_t *st);

#endif /* STACK_H_XXX*/
