/*==============================================================================
Data Structures - Binary Search Tree
OL66
Version 1
==============================================================================*/

#ifndef ILRD_BST_H
#define ILRD_BST_H

#include <stddef.h> /* size_t */

/* handle for a BST */
typedef struct bst_s bst_t;

/*
    bst iterator

    after insertion / removal, iterators become invalid.
*/
typedef struct triter_s
{
    void *info;
}triter_t;

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
typedef int (*bst_cmp_t) (const void *data, const void *tree_data);

/*
    operation function. Used in ForEach
    perfoems operation on a tree member

    args:
        tree_data: data already in tree
        arg: optional additional argument

    returns:
        0 on success, appropriate error code on failure

*/
typedef int (*bst_op_t) (void *tree_data, void *arg);

/*
    create a new tree

    args:
        sorting_method:

    returns handle to new tree, NULL on failure

    complexity O(1)
*/
bst_t *BSTCreate(bst_cmp_t sorting_method);

/*
    destroy tree. free all related memory

    args:
        tree - a bst_t handle

    complexity O(n)
*/
void BSTDestroy(bst_t *tree);

/*
    counts members of tree

    args:
        tree - a bst_t handle

    return:
        tree member count

    complexity O(n)
*/
size_t BSTCount(const bst_t *tree);

/*
    checks whether tree has no members

    args:
        tree - a bst_t handle

    return:
        boolean

    complexity O(1)
*/
int BSTIsEmpty(const bst_t *tree);

/*
    inserts a member to tree.

    args:
        tree - a bst_t handle
        data - new member data

    returns iterator to new member, end of tree on failure

    complexity O(log(n))
*/
triter_t BSTInsert(bst_t *tree, void *data);

/*
    delete a member from tree.

    args:
        tree - a bst_t handle
        data - member data

	returns:
		next of iter

    complexity O(log(n))
*/
triter_t BSTRemove(triter_t iter);

/*
    performs an operation on iterators in range,
    NOT INCLUDING to

    args:
        tree - a bst_t handle
        operation - function to be called. Must conform to bst_op_t
        arg - optional additional arguments of operation

    returns:
        0 on success (went through all iterators)
        appropriate error code on failure

    complexity O(n)
*/
int BSTForEach(triter_t from, triter_t to, bst_op_t operation, void *arg);

/*
    searches the tree for a member by data

    args:
        tree - a bst_t handle
        data -

    returns:
		iterator on success, end of tree on failure

    complexity O(log(n))
*/
triter_t BSTFind(bst_t *tree, const void *data);

/*
    get iterator to first member of tree, in order

    args:
        tree: bst_t handle

    returns iterator to beginning of tree

    complexity O(log(n))
*/
triter_t BSTBegin(const bst_t *tree);

/*
    get iterator to last member of tree

    args:
        tree: bst_t handle

    returns iterator to end of tree

    complexity O(log(n))
*/
triter_t BSTEnd(const bst_t *tree);

/*
    get iterator to next member of tree

    args:
        iter - iterator to a member of a tree

    returns iterator to next member of tree

    complexity O(lon(n))
*/
triter_t BSTNext(triter_t iter);

/*
    get iterator to previous member of tree

    args:
        iter - iterator to a member of a tree

    returns iterator to previous member of tree

    complexity O(lon(n))
*/
triter_t BSTPrev(triter_t iter);

/*
    get data from iterator

    args:
        iter - iterator to a member of a tree

    returns iterator member's data

    complexity O(1)
*/
void *BSTGetData(triter_t iter);

/*
	Check whether two iterators are identical

	args:
		iter1, iter2 - iterators to compare

	returns:
		boolean
*/
int BSTIsSameIter(triter_t iter1, triter_t iter2);

#endif /* ILRD_BST_H */
