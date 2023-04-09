/*==============================================================================
Data Structures - Hash
Module
Dekel Sror
Review - Maor Alankri
Version 2
==============================================================================*/
#include <stdlib.h> /* malloc, free                     */
#include <assert.h>

#include "dllist.h" /* dlist_t, diter_t, dlist API      */
#include "hash.h"   /* hash_t , hash_cmp_t, hash_func_t */

struct hash_s
{
    hash_func_t hash_function;
    hash_cmp_t collision_compare_method;
    size_t hash_size;
    dlist_t *table[1];
};

typedef int (*dlist_opt_t)(void *data, void *argument);

static diter_t NodeFind(hash_t *hash_table, const void *value);

hash_t *HashCreate(hash_func_t hash_function,
                   hash_cmp_t collision_compare_method,
                   size_t hash_size)
{
    size_t i = 0;
    int fail_index = -1;

    hash_t *new_hash = malloc(sizeof(hash_t) + hash_size * sizeof(dlist_t *));

    if (NULL == new_hash)
    {
        return NULL;
    }

    new_hash->hash_size = hash_size;
    new_hash->hash_function = hash_function;
    new_hash->collision_compare_method = collision_compare_method;

    for (i = 0; i < hash_size; ++i)
    {
        new_hash->table[i] = DLCreate();

        if (NULL == new_hash->table[i])
        {
            fail_index = i;
            break;
        }
    }

    if (fail_index > -1)
    {
        while (0 <= fail_index)
        {
            DLDestroy(new_hash->table[i]);
            --fail_index;
        }

        free(new_hash);
        new_hash = NULL;
    }

    return new_hash;
}

void HashDestroy(hash_t *hash_table)
{
    size_t i = 0;

    assert(hash_table);

    for (i = 0; i < hash_table->hash_size; ++i)
    {
        DLDestroy(hash_table->table[i]);
    }

    free(hash_table);

    hash_table = NULL;
}

size_t HashCount(const hash_t *hash_table)
{
    size_t count = 0;
    size_t i = 0;

    assert(hash_table);

    for (i = 0; i < hash_table->hash_size; ++i)
    {
        count += DLCount(hash_table->table[i]);
    }

    return count;
}

int HashIsEmpty(const hash_t *hash_table)
{
    size_t i = 0;

    assert(hash_table);

    for (i = 0; i < hash_table->hash_size; ++i)
    {
        if (!DLIsEmpty(hash_table->table[i]))
        {
            return 0;
        }
    }

    return 1;
}

int HashInsert(hash_t *hash_table, void *value)
{
    size_t index = 0;
    diter_t diter = { 0 };

    assert(hash_table);
    assert(value);

    index = hash_table->hash_function(value);
    diter = DLPushFront(hash_table->table[index] , value);

    /* 0 success, 1 err DLPush failed */
    return DLIsSameIter(diter, DLEnd(hash_table->table[index]));
}

void HashRemove(hash_t *hash_table, const void *value)
{
    size_t index = 0;
    diter_t diter = { 0 };

    assert(hash_table);
    assert(value);

    index = hash_table->hash_function(value);

    diter = NodeFind(hash_table, value);

    if (!DLIsSameIter(diter, DLEnd(hash_table->table[index])))
    {
        DLErase(diter);
    }
}

int HashForEach(hash_t *hash_table, hash_op_t operation, void *arg)
{
    size_t i = 0;
    int res = 0;

    assert(hash_table);

    for (i = 0; (i < hash_table->hash_size) && (res == 0); ++i)
    {
        res = DLForEach(DLBegin(hash_table->table[i]),
                        DLEnd(hash_table->table[i]),
                        (dlist_opt_t)operation,
                        arg);

        if (0 != res)
        {
            break;
        }

    }

    return res;
}

static diter_t NodeFind(hash_t *hash_table, const void *value)
{
    size_t index = 0;

    assert(hash_table);
    assert(value);

    index = hash_table->hash_function(value);

    return DLFind
            (
                DLBegin(hash_table->table[index]),
                DLEnd(hash_table->table[index]),
                hash_table->collision_compare_method,
                value
            );
}

void *HashFind(hash_t *hash_data, const void *value)
{
    assert(hash_data);
    assert(value);

    return DLGetData(NodeFind(hash_data, value));
}
