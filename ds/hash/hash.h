/*==============================================================================
Data Structures - Hash
Header
Dekel Sror
Review - Maor Alankri
Version 1
==============================================================================*/
#ifndef ILRD_HASH_H
#define ILRD_HASH_H

#include <stddef.h> /* size_t */

/* handle for a hash table */

typedef struct hash_s hash_t;


/*
    hash function derives key from value

    args:
    value - value for hashing

    returns hashed index for given value

*/
typedef size_t (*hash_func_t)(const void *value);

/*
    compare function between value and hash_table

    args:
                value - value provided
                hash_value - value in hash table

    returns 0 for eqaulity, else !0
*/
typedef int (*hash_cmp_t)(const void *value,
                          const void *hash_value);

/*
        operation function. Used in ForEach
    perfoems operation on a hash table members

    args:
        value- data already in hash table
        arg- optional additional argument

    returns:
        0 on success, !0 one of iterations returned !0

*/
typedef int (*hash_op_t)(const void *hash_value, void *arg);
/*
    create a new hash table

    args:
        hash function
        compare function
        hash_size - range of indices

    returns handle to hash table

    complexity O(1)
*/
hash_t *HashCreate(hash_func_t hash_function,
                   hash_cmp_t compare_function,
                   size_t hash_size);

/*
    destroy hash table. free all related memory

    args:
        hash_table - a hash_t handle
*/
void HashDestroy(hash_t *hash_table);

/*
    counts occupied members of hash table

    args:
        hash table - a hash_t handle

    return:
        hash table occupied member count

*/
size_t HashCount(const hash_t *hash_table);

/*
    checks whether hash_table is empty

    args:
        hash_table - a hash_t handle

    return:
        0 - empty !0 - not empty

*/

int HashIsEmpty(const hash_t *hash_table);

/*
    inserts a member to hash_table.

    args:
        hash_table - a hash_t handle
        value - new member data

    returns 0 on success and !0 on failure

    complexity O(1)
*/
int HashInsert(hash_t *hash_table, void *value);

/*
    delete a member from hash_table.

    args:
        hash_table - a hash_t handle
        value - member value

    complexity O(1)
*/
void HashRemove(hash_t *hash_table, const void *value);

/*
    performs an operation on all members in hash table

    args:
        hash_table - a hash_t handle
        operation - function to be called. Must conform to HASH_op_t
        arg - optional additional arguments of operation

    returns:
        0 ran through all members
        !0 one of iterations returned !0

    complexity O(n)
*/
int HashForEach(hash_t *hash_table,
                hash_op_t operation,
                void *arg);

/*
    searches the hash_table for a member by value

    args:
        hash_table - a hash_t handle
        value - value to be found

    returns:
        if found, pointer to value, otherwise NULL

    complexity O(1)
*/
void *HashFind(hash_t *hash_table,
                     const void *value);

#endif /* ILRD_HASH_H */
