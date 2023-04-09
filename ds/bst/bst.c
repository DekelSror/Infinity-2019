/*==============================================================================
Data Structures - binary Search Tree
Module
Dekel Sror
Review - Marcel Binyaminov
RC 1
==============================================================================*/
#include <assert.h> /* assert */
#include <stdlib.h> /* malloc, free, NULL */

#include "bst.h"

typedef struct node_s node_t;

struct node_s
{
    void *data;
    node_t *children[2];
    node_t *parent;
};

/* handle for a BST */
struct bst_s
{
    node_t *root;
    bst_cmp_t sorting_method;
};

#define HAS_CHILD(node, side) (NULL != node->children[side])
#define IS_CHILD(node, side) (node == (node->parent->children[side]))

#define NODE_TO_ITER(iter, node) (iter.info = (void *)node)
#define ITER_TO_NODE(iter) ((node_t *)iter.info)

typedef enum { LEFT , RIGHT } sides_t;

/* traversal function */
static triter_t Step(triter_t iter, sides_t edge);

/* node related functions */
static node_t *NodeCreate(void *data);
static void NodeDelete(node_t *node);
static void AddChild(node_t *parent, node_t *child, sides_t side);

bst_t *BSTCreate(bst_cmp_t sorting_method)
{
    bst_t *new_tree = malloc(sizeof(bst_t));

    if (NULL == new_tree)
    {
        return NULL;
    }

    new_tree->root = NodeCreate((void *)0xDEADBEEF);

    if (NULL == new_tree->root)
    {
        free(new_tree);
        new_tree = NULL;

        return NULL;
    }

    new_tree->sorting_method = sorting_method;

    return new_tree;
}

void BSTDestroy(bst_t *tree)
{
    triter_t deleter = { 0 };
    triter_t end = { 0 };

    assert(tree);

    deleter = BSTBegin(tree);
    end = BSTEnd(tree);

    while (!BSTIsSameIter(deleter, end))
    {
        deleter = BSTRemove(deleter);
    }

    free(tree->root);

    tree->root = NULL;

    free(tree);

    tree = NULL;
}

size_t BSTCount(const bst_t *tree)
{
    size_t count = 0;
    triter_t iter = { 0 };
    triter_t end = { 0 };

    assert(tree);

    iter = BSTBegin(tree);
    end = BSTEnd(tree);

    while (!BSTIsSameIter(iter, end))
    {
        ++count;
        iter = BSTNext(iter);
    }

    return count;
}

triter_t BSTInsert(bst_t *tree, void *data)
{
    sides_t edge = LEFT;
    node_t *node = NULL;
    triter_t iter = { 0 };

    node_t *new_child = NodeCreate(data);

    assert(tree);
    assert(data);

    if (NULL == new_child)
    {
        return BSTEnd(tree);
    }

    node = tree->root;

    while (HAS_CHILD(node, edge))
    {
        node = node->children[edge];
        edge = (0 < tree->sorting_method(data, node->data));
    }

    AddChild(node, new_child, edge);

    NODE_TO_ITER(iter, new_child);

    return iter;
}

triter_t BSTRemove(triter_t iter)
{
    node_t *node = ITER_TO_NODE(iter);
    node_t *to_delete = node;
    sides_t node_branch = IS_CHILD(node, RIGHT);

    iter = BSTNext(iter);

    /* no children - detach */
    if (!HAS_CHILD(node, RIGHT) && (!HAS_CHILD(node, LEFT)))
    {
        node->parent->children[node_branch] = NULL;
    }

    /* one child - link parent to that child */
    else if (HAS_CHILD(node, RIGHT) ^ HAS_CHILD(node, LEFT))
    {
        sides_t child_branch = HAS_CHILD(node, RIGHT);

        node->parent->children[node_branch] = node->children[child_branch];
        node->children[child_branch]->parent = node->parent;
    }

    /* two children - connect parent to next of node (leftmost of its right branch) */
    else
    {
        node_t *next = ITER_TO_NODE(iter);

        node->data = next->data;
        next->parent->children[IS_CHILD(next, RIGHT)] = next->children[RIGHT];

        if (HAS_CHILD(next, RIGHT))
        {
          next->children[RIGHT]->parent = next->parent;
        }

        to_delete = next;
        NODE_TO_ITER(iter, next->parent);
    }

    NodeDelete(to_delete);

    return iter;
}


triter_t BSTFind(bst_t *tree, const void *data)
{
    node_t *node = NULL;
    sides_t edge = LEFT;
    int found = 0;
    triter_t res = { 0 };

    assert(tree);
    assert(data);

    node = tree->root;

    while (HAS_CHILD(node, edge))
    {
        int compare_result = 0;

        node = node->children[edge];

        compare_result = tree->sorting_method(data, node->data);
        edge = compare_result > 0;

        if (0 == compare_result)
        {
            found = 1;
            break;
        }
    }

    if (found)
    {
        NODE_TO_ITER(res, node);
    }
    else
    {
        res = BSTEnd(tree);
    }

    return res;
}

int BSTForEach(triter_t from, triter_t to, bst_op_t operation, void *arg)
{
    int res = 0;

    while (!BSTIsSameIter(from, to))
    {
        res = operation(ITER_TO_NODE(from)->data, arg);

        if (0 != res)
        {
            break;
        }

        from = BSTNext(from);
    }

    return res;
}

triter_t BSTNext(triter_t iter)
{
    return Step(iter, RIGHT);
}

triter_t BSTPrev(triter_t iter)
{
    return Step(iter, LEFT);
}

triter_t BSTBegin(const bst_t *tree)
{
    triter_t begin = { 0 };
    node_t *node = NULL;

    assert(tree);

    node = tree->root;

    while (HAS_CHILD(node, LEFT))
    {
        node = node->children[LEFT];
    }

    NODE_TO_ITER(begin, node);

    return begin;
}

triter_t BSTEnd(const bst_t *tree)
{
    triter_t res = { 0 };

    assert(tree);

    NODE_TO_ITER(res, tree->root);

	return res;
}

void *BSTGetData(triter_t iter)
{
    return ITER_TO_NODE(iter)->data;
}

int BSTIsEmpty(const bst_t *tree)
{
    assert(tree);

    return (!HAS_CHILD(tree->root, RIGHT) && !HAS_CHILD(tree->root, LEFT));
}

int BSTIsSameIter(triter_t iter1, triter_t iter2)
{
    return iter1.info == iter2.info;
}



/* traversal function - called with LEFT for previous, RIGHT for next  */
static triter_t Step(triter_t iter, sides_t edge)
{
    node_t *node = ITER_TO_NODE(iter);

    if (HAS_CHILD(node, edge))
    {
        node = node->children[edge];

        while (HAS_CHILD(node, !edge))
        {
            node = node->children[!edge];
        }
    }
    else
    {
        while (IS_CHILD(node, edge))
        {
            node = node->parent;
        }

        node = node->parent;
    }

    NODE_TO_ITER(iter, node);

    return iter;
}

/* static functions - node 'API' */
static void AddChild(node_t *parent, node_t *child, sides_t side)
{
    parent->children[side] = child;
    child->parent = parent;
}

static node_t *NodeCreate(void *data)
{
    node_t *new_node = malloc(sizeof(node_t));

    if (NULL == new_node)
    {
        return NULL;
    }

    new_node->data = data;
    new_node->children[LEFT] = NULL;
    new_node->children[RIGHT] = NULL;
    new_node->parent = NULL;

    return new_node;
}

static void NodeDelete(node_t *node)
{
    assert(node);

    free(node);

    node = NULL;
}
