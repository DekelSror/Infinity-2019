/*==============================================================================
Data Structures - Vector
Header
Dekel Sror
Review - Moti Zamir
RC 1
==============================================================================*/

#ifndef DYNAMIC_VECTOR
#define DYNAMIC_VECTOR

#include <stddef.h> /* size_t */

/* type of vector */
typedef struct vector_t vector_t;

/* initializes a vector struct */
/* arguments:
      element_size
      num_of_elements

   return pointer to a vector_t instance
   returns NULL if element_size/num_of_elements is 0.
*/
vector_t *VectorCreate(size_t element_size
                      ,size_t num_of_elements);

/* frees the memory allocated for the data array */
/*
    arguments:
        vector_t pointer
    frees all memory associated with vector
*/
void VectorDestroy(vector_t *vector);

/* appends the given value to the vector */
/*
    arguments:
        vector_t pointer, value
    appends value to given vector
    returns success(0) / fail(1)
*/
int VectorPush(vector_t *vector, const void *value);
/* Pops the last element of the vector */
/*
    arguments:
        vector_t pointer
*/
/* if the vector is empty result is undefined */
void VectorPop(vector_t *vector);
/* get the address of the element at the given index */
/*
    arguments:
        vector_t pointer
        index
*/
/* pushing or resizing may result in a dangling pointer */
/* for invalid indices the behaviour is undefined */
void *VectorGet(vector_t *vector, size_t index);
/* returns num of elements in vector */
/*
    arguments:
        vector_t pointer
*/
size_t VectorSize(const vector_t *vector);
/* returns the current capacity of the vector */
/*
    arguments:
        vector_t pointer
*/
size_t VectorCapacity(vector_t *vector);
/* Resize vector capacity, elements out of the new capacity, will be removed */
/*
    arguments:
        vector_t pointer
        num_of_elements

    returns success(0) / fail(1)
*/
int VectorResize(vector_t *vector, size_t num_of_elements);

#endif /* DYNAMIC_VECTOR */
