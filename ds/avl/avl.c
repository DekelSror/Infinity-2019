/*==============================================================================
Data Structures - AVL Tree
Module
Dekel Sror
Review - Shon Weinberg
RC 1
==============================================================================*/
#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert */

#include "avl_node.h" /* avl_node_t, recursive node API */
#include "avl.h"

/* AVL tree handle */
struct avl_s
{
		avl_node_t *root;
		avl_cmp_t sorting_method;
};

avl_t *AVLCreate(avl_cmp_t sorting_method)
{
	avl_t *new_tree = malloc(sizeof(avl_t));

	if (NULL == new_tree)
	{
		return NULL;
	}

	new_tree->root = NULL;
	new_tree->sorting_method = sorting_method;

	return new_tree;
}

void AVLDestroy(avl_t *tree)
{
	assert(tree);

	NodeFreeAll(tree->root);

	free(tree);

	tree = NULL;
}

size_t AVLCount(const avl_t *tree)
{
	assert(tree);

	return NodeCount(tree->root);
}

int AVLIsEmpty(const avl_t *tree)
{
	assert(tree);

	return (NULL == tree->root);
}

int AVLInsert(avl_t *tree, void *data)
{
	avl_node_t *new_node = NodeCreate(data);

	assert(tree);

	if (NULL == new_node)
	{
		return 1; /* err nomem */
	}

	tree->root = NodeInsert(tree->root, new_node, tree->sorting_method);

	return 0;
}

void AVLRemove(avl_t *tree , const void *data)
{
	assert(tree);
	assert(data);

	tree->root = NodeRemove(tree->root, data, tree->sorting_method);
}

int AVLForEach(avl_t *tree, avl_op_t operation, void *arg)
{
	assert(tree);

	return NodeForEach(tree->root, operation, arg);
}

void *AVLFind(const avl_t *tree, const void *data)
{
	avl_node_t *node = NULL;

	assert(tree);
	assert(data);

	node = NodeFind(tree->root, tree->sorting_method, data);

	if (NULL == node)
	{
		return NULL;
	}

	return NodeGetData(node);
}

size_t AVLHeight(const avl_t *tree)
{
	assert(tree);

	return NodeHeight(tree->root);
}
