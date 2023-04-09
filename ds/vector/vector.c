/*==============================================================================
Data Structures - Vector
Module
Dekel Sror
Review - Moti Zamir
RC 1
==============================================================================*/

#include <stdlib.h> /* malloc, free, NULL */
#include <string.h> /* memcmp, memcpy */
#include <assert.h> /*  assert */

#include "vector.h"

#define MIN2(a, b) ((a) > (b) ? (b) : (a))

struct vector_t
{
    size_t length;
    size_t element_size;
    size_t capacity;
    char *data;
};

vector_t *VectorCreate(size_t element_size ,size_t num_of_elements)
{
    vector_t *new_vector = (vector_t*)malloc(sizeof(vector_t));

    assert(element_size > 0);
    assert(num_of_elements > 0);

    if (NULL == new_vector)
    {
        return NULL;
    }

    new_vector->data = (char *)malloc(element_size * num_of_elements);

    if (NULL == new_vector->data)
    {
        free (new_vector);
        new_vector = NULL;
        return NULL;
    }

    new_vector->length = 0;
    new_vector->element_size = element_size;
    new_vector->capacity = num_of_elements;

    return new_vector;
}

void VectorDestroy(vector_t *vector)
{
    assert(vector);

    free(vector->data);
    vector->data = NULL;

    free(vector);
    vector = NULL;
}

int VectorPush(vector_t *vector, const void *value)
{

    assert(vector);
    assert(value);

    if (vector->length == vector->capacity)
    {
        int resize_err = VectorResize(vector, vector->capacity * 2);

        if (0 != resize_err)
        {
            return resize_err;
        }
    }

    memcpy(vector->data + (vector->length * vector->element_size)
           , value, vector->element_size);

    ++vector->length;

    return 0;
}


int VectorResize(vector_t *vector, size_t num_of_elements)
{
    char *new_data = (char*)malloc(vector->element_size * num_of_elements);

    size_t at_least = MIN2(num_of_elements, vector->capacity)
                            * vector->element_size;

    assert(vector);

    if (NULL == new_data)
    {
/* errcode MALLOC_FAIL */
        return 1;
    }

    memcpy(new_data, vector->data, at_least);

    if (0 != memcmp(new_data, vector->data, at_least))
    {
        free(new_data);
        new_data = NULL;
/* errcode MEMCPY_FAIL */
        return 2;
    }

    vector->capacity = num_of_elements;
    vector->length = MIN2(vector->length, num_of_elements);
    free (vector->data);
    vector->data = new_data;
    new_data = NULL;

    return 0;
}

void VectorPop(vector_t *vector)
{
    assert(vector);

    --vector->length;
}

void *VectorGet(vector_t *vector, size_t index)
{
    assert(vector);

    return vector->data + index * vector->element_size;
}

size_t VectorSize(const vector_t *vector)
{
    assert(vector);

    return vector->length;
}

size_t VectorCapacity(vector_t *vector)
{
    assert(vector);

    return vector->capacity;
}
