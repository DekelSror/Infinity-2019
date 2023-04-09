/*==============================================================================
Quiz - Int Stack - wrapper on stack
Header
Dekel Sror
Version 1
==============================================================================*/
#ifndef ISTACK_DEKEL
#define ISTACK_DEKEL

typedef struct istack_s istack_t;

/*
    create a new instance
*/
istack_t *IntStackCreate(size_t num_of_elems);

/*
    destroys st, frees all associated memory
*/
void IntStackDestroy(istack_t *st);

/*
    push integer num to st
*/
void IntStackPush(istack_t *st, int num);

/*
    pop (last in) from st
*/
void IntStackPop(istack_t *st);

/*
    return head of st
*/
int IntStackPeek(istack_t *st);

/*
    returns stack size of st
*/
size_t IntStackSize(const istack_t *st);

#endif /* ISTACK_DEKEL */
