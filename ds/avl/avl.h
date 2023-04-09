/*==============================================================================
Data Structures - AVL Tree
OL66
Version 1
==============================================================================*/

#ifndef ILRD_AVL_H
#define ILRD_AVL_H

#include <stddef.h> /* size_t */

/* handle for a AVL */
typedef struct avl_s avl_t;

/*
    sorting rule for the tree. Used in insert and find

    args:
        data : data to insert or find
        tree_data: data already in tree

    return:
        positive if data will be right child of tree_data
        negative if data will be left chlid of tree_data
        0 - equality. For insert, 0 will cause undefined behaviour,
        as tree doesn't support duplicates
*/
typedef int (*avl_cmp_t) (const void *data, const void *tree_data);

/*
    operation function. Used in ForEach
    perfoems operation on a tree member

    args:
        tree_data: data already in tree
        arg: optional additional argument

    returns:
        0 on success, appropriate error code on failure

*/
typedef int (*avl_op_t) (void *tree_data, void *arg);

/*
    create a new tree

    args:
        sorting_method:

    returns handle to new tree, NULL on failure

    complexity O(1)
*/
avl_t *AVLCreate(avl_cmp_t sorting_method);

/*
    TODO post order implementation
    destroy tree. free all related memory

    args:
        tree - a avl_t handle

    complexity O(n)
*/
void AVLDestroy(avl_t *tree);

/*
    TODO pre order implementation
    counts members of tree

    args:
        tree - a avl_t handle

    return:
        tree member count

    complexity O(n)
*/
size_t AVLCount(const avl_t *tree);

/*
    checks whether tree has no members

    args:
        tree - a avl_t handle

    return:
        boolean

    complexity O(1)
*/
int AVLIsEmpty(const avl_t *tree);

/*
    inserts a member to tree.

    args:
        tree - a avl_t handle
        data - new member data

    return:
      0 - success, !0 - failure;

    complexity O(log(n))
*/
int AVLInsert(avl_t *tree, void *data);

/*
    delete a member from tree.

    args:
        tree - a avl_t handle
        data - member data

    complexity O(log(n))
*/
void AVLRemove(avl_t *tree , const void *data);

/*
    TODO in order implementation
    performs an operation on tree,

    args:
        tree - a avl_t handle
        operation - function to be called. Must conform to avl_op_t
        arg - optional additional arguments of operation

    returns:
        0 on success, !0 on failure

    complexity O(n)
*/
int AVLForEach(avl_t *tree, avl_op_t operation, void *arg);

/*
    searches the tree for a member by data

    args:
        tree - a avl_t handle
        data - data to be found

    returns:
                    pointer to data in the tree.
        if data doesn't exist, returns NULL.

    complexity O(log(n))
*/
void *AVLFind(const avl_t *tree, const void *data);

/*
    returns height of current tree;

    args:
        tree - a avl_t handle

    returns:
                    height of tree

    complexity O(1)
*/
size_t AVLHeight(const avl_t *tree);

#endif /* ILRD_AVL_H */
