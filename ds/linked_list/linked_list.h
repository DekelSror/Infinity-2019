/*==============================================================================
Data Structures - Singly Linked List
Header
Dekel Sror
Review: Maor Alankri
OL66
Version 2
==============================================================================*/
#ifndef _LINKED_LIST_H
#define _LINKED_LIST_H

#include <stddef.h> /* size_t */

typedef struct node_s
{
    struct node_s *next;
    void *data;
} node_t;

typedef int (*operation_t)(void *data, void *arg);
typedef int (*compare_t)(const void *data, const void *arg);

/***************************************************/

/* For all operations, if arguments are invalid - behaviour is undefined */

/*
    Creates a new node
    args -
        data - pointer to the data
        next - pointer to next link

    returns a node_t pointer to a new node_t instance.

    complexity O(1)
*/
node_t *ListCreateNode(void *data, node_t *next);

/*
    Insert to_insert before post_node
    args -
            to_insert: the node to be inserted
            post_node: where in the list

    returns pointer to to_insert.

            complexity O(1)
*/
node_t *ListInsert(node_t *to_insert, node_t *post_node);

/*
    Inserts a to_insert before pre_node
    args -
            to_insert: the node to be inserted
            pre_node: the node to be previous

    returns pointer to to_insert.

            complexity O(1)
*/
node_t *ListInsertAfter(node_t *to_insert, node_t *pre_node);

/*
    removes to_remove from list.
    args-
            to_remove: node to be removed

    returns to_remove

    complexity O(1)

    Behaviour for last link in list is undefined
*/
node_t *ListRemove(node_t *to_remove);

/*
    removes node after pre_remove.
    args-
            pre_remove: node preceeding node to be removed

    returns pre_remove

    complexity O(1)

    Behaviour for last link in list is undefined
*/
node_t *ListRemoveAfter(node_t *pre_remove);

/*
    returns the number of nodes in a list
    args-
            head - pointer to the head of the list

    returns the number of nodes

    complexity O(n)
*/
size_t ListCount(const node_t *head);

/*
    Search for data inside a linked list

    -args:
        head - head of the list
        data - the data to be found
        cmp - the compare funcion

    returns a pointer to the node if found

    if data is not found, return NULL.

    complexity O(n) * complexity of cmp
*/

node_t *ListFind(const node_t *head, const void *data, compare_t cmp);

/*
    free all members of a given list

    -args:
        head - head of the list

    complexity O(n)
*/
void ListFreeAll(node_t *head);

/*
    For each node in a given list, perform a given operation

    -args:
        head - head of the list
        operation - the function to be performed
        arg - argument for operation
    return
            the status from the operation function
    complexity O(n) * complexity of operation
*/
int ListForEach(node_t *head, operation_t operation, void *arg);

/*
    Flip order of elements in a given list

    -args:
        head - head of the list

    return:
        pointer to new head after flip

    complexity O(n)
*/
node_t *ListFlip(node_t *head);

/*
    Search for a loop inside a given list

    -args:
        head - head of the list

        if loop was found return true, else false

    complexity O(n)
*/
int ListHasLoop(const node_t *head);

/*
    Search for a intersection between 2 given lists

    -args:
        l1 - head of first list
        l2 - head of second list

        if intersection is found, returns pointer to the intesecting node,
        if no, returns NULL.

    complexity O(n + m)
*/
const node_t *ListFindIntersection(const node_t *l1, const node_t *l2);

/* utility */
void ListPrint(const node_t *list);


#endif /* _LINK_LIST_H */
