/*==============================================================================
Data Structures - Singly Linked List
Module
Dekel Sror
Review: Maor Alankri
OL66
Version 2
==============================================================================*/
#include <stdlib.h> /* malloc, free, NULL */
#include <stdio.h>  /* ListPrint printf   */
#include <assert.h> /* assert             */

#include "linked_list.h"

node_t *ListCreateNode(void *data, node_t *next)
{
    node_t *new_node = (node_t *)malloc(sizeof(node_t));

    if (NULL == new_node)
    {
        return NULL;
    }

    new_node->data = data;
    new_node->next = next;

    return new_node;
}

node_t *ListInsert(node_t *to_insert, node_t *post_node)
{
    void *data_p = NULL;

    assert(to_insert);
    assert(post_node);

    data_p = post_node->data;
    post_node->data = to_insert->data;
    to_insert->data = data_p;

    return ListInsertAfter(to_insert, post_node);
}

node_t *ListInsertAfter(node_t *to_insert, node_t *pre_node)
{
    assert(to_insert);
    assert(pre_node);

    to_insert->next = pre_node->next;
    pre_node->next = to_insert;

    return pre_node ;
}

node_t *ListRemove(node_t *to_remove)
{
    assert(to_remove);

    to_remove->data = to_remove->next->data;

    return ListRemoveAfter(to_remove);
}

node_t *ListRemoveAfter(node_t *pre_remove)
{
    node_t *delete = NULL;

    assert(pre_remove);

    delete = pre_remove->next;
    pre_remove->next = pre_remove->next->next;

    free(delete);
    delete = NULL;

    return pre_remove;
}

size_t ListCount(const node_t *head)
{
    size_t count = 0;

    assert(head);

    while (head)
    {
        head = head->next;
        ++count;
    }

    return count;
}

void ListFreeAll(node_t *head)
{
    node_t *p_next = NULL;

    assert(head);

    p_next = head->next;

    while (p_next)
    {
        free(head);
        head = p_next;
        p_next = p_next->next;
    }

    free(head);
    head = NULL;
    p_next = NULL;
}

int ListForEach(node_t *head, operation_t operation, void *arg)
{

    assert(head);
    assert(arg);

    while (head)
    {
        int op_err = operation(head->data, arg);

        if (op_err)
        {
            return op_err;
        }

        head = head->next;
    }

    return 0;
}

node_t *ListFind(const node_t *head, const void *data, compare_t cmp)
{
    node_t *runner = (node_t *)head;

    assert(head);
    assert(data);

    while (runner)
    {
        if (cmp(runner->data, data))
        {
            return runner;
        }
        runner = runner->next;
    }

    return NULL;
}

node_t *ListFlip(node_t *head)
{
    node_t *runner = head;
    node_t *next_holder = head;
    node_t *prev = head;

    assert(head);

/* to each next, assign the previous element */
    while (next_holder)
    {
        prev = runner;
        runner = next_holder;
        next_holder = runner->next;
        runner->next = prev;
    }
/* last step - make the first element the last */
    head->next = NULL;

    return runner;
}

int ListHasLoop(const node_t *head)
{
    const node_t *run_fast = head;
    const node_t *run_slow = head;

    assert(head);

    while ((NULL != run_slow) && (NULL != run_fast))
    {
        if (run_fast->next && run_fast->next->next)
        {
            run_fast = run_fast->next->next;
        }
        else
        {
/* reached end of list - no loop */
            return 0;
        }

        run_slow =run_slow->next;

/* loop break condition */
        if ((run_fast == run_slow))
        {
            return 1;
        }
    }

    return 0;
}

const node_t *ListFindIntersection(const node_t *l1, const node_t *l2)
{
    size_t len1 = 0;
    size_t len2 = 0;
    const node_t *p_shorter = NULL;
    const node_t *p_longer = NULL;
    long diff = 0;
    size_t i = 0;

    assert(l1);
    assert(l2);

    len1 = ListCount(l1);
    len2 = ListCount(l2);

/* assign pointers to lists by their respective lengths */
    p_longer = (len1 >= len2) ? l1 : l2;
    p_shorter = (p_longer == l1) ? l2 : l1;

    diff = (long)len1 - (long)len2;
    diff = (diff < 0) ? -diff : diff;

/* 'shorten' the long list */
    for (i = 0; i < (size_t)diff; ++i)
    {
        p_longer = p_longer->next;
    }

    while ((NULL != p_shorter) && (NULL != p_longer))
    {
        if (p_shorter == p_longer)
        {
            return p_shorter;
        }

        p_shorter = p_shorter->next;
        p_longer = p_longer->next;
    }
    return NULL;
}


void ListPrint(const node_t *list)
{

    printf("\n===================================\n");

    while (NULL != list)
    {
        printf("%d, ", *(int *)list->data);
        list = list->next;
    }

    printf("\n===================================\n\n");
}
