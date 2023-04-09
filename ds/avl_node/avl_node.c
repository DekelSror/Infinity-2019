/*==============================================================================
Data Structures - AVL Tree
Recursive node module
Dekel Sror
Review - Shon Weinberg
RC 1
==============================================================================*/
#include <stdlib.h> /* malloc, free */

#include "avl_node.h"

/* maximum difference between node's branches heights */
#define DIFF_TOLERANCE (1)

#define MAX2(a, b) (((a) > (b)) ? (a) : (b))

#define BRANCH_DIFF(node) ((int)NodeHeight(node->children[RIGHT]) -\
						   (int)NodeHeight(node->children[LEFT]))

#define UPDATE_NODE_HEIGHT(node)\
    (node->height = MAX2(NodeHeight(node->children[LEFT]),\
                         NodeHeight(node->children[RIGHT])) + 1)

#define HAS_CHILD(node, side) (NULL != node->children[side])

struct avl_node_s
{
	void *data;
	avl_node_t *children[2];
	size_t height;
};

static avl_node_t *NodeBalance(avl_node_t *node);
static avl_node_t *NodeDelete(avl_node_t *node, avl_cmp_t cmp);
static avl_node_t *NextNode(avl_node_t *node);
static avl_node_t *NodeRotate(avl_node_t *root, sides_t side);
static avl_node_t *LeftLeft(avl_node_t *node);
static avl_node_t *LeftRight(avl_node_t *node);
static avl_node_t *RightLeft(avl_node_t *node);
static avl_node_t *RightRight(avl_node_t *node);

avl_node_t *NodeCreate(void *data)
{
	avl_node_t *new_node = malloc(sizeof(avl_node_t));

    if (NULL == new_node)
	{
		return NULL;
	}

	new_node->data = data;
	new_node->children[LEFT] = NULL;
	new_node->children[RIGHT] = NULL;
	new_node->height = 1;

	return new_node;
}

void NodeFreeAll(avl_node_t *node)
{
	if (NULL == node)
	{
		return;
	}

	NodeFreeAll(node->children[LEFT]);
	NodeFreeAll(node->children[RIGHT]);

	node->children[LEFT] = NULL;
	node->children[RIGHT] = NULL;

	free(node);
	node = NULL;
}

size_t NodeCount(avl_node_t *node)
{
	if (NULL == node)
	{
		return 0;
	}

	return 1 + NodeCount(node->children[LEFT]) +
		  	   NodeCount(node->children[RIGHT]);
}

int NodeForEach(avl_node_t *node, avl_op_t operation, void *arg)
{
	int res = 0;

	if (NULL == node)
	{
		return 0;
	}

	res =  NodeForEach(node->children[LEFT], operation, arg);
	res =  operation(node->data, arg);
	res =  NodeForEach(node->children[RIGHT], operation, arg);

	return res;
}

avl_node_t *NodeFind(avl_node_t *node, avl_cmp_t cmp, const void *data)
{
	if (NULL == node)
	{
		return NULL;
	}
	else
	{
        int res_cmp = cmp(data, node->data);

		if (0 == res_cmp)
		{
			return node;
		}
		else
		{
            return NodeFind(node->children[0 > res_cmp], cmp, data);
		}
	}
}

size_t NodeHeight(avl_node_t *node)
{
	if (NULL == node)
	{
		return 0;
	}

	return node->height;
}

avl_node_t *NodeInsert(avl_node_t *node, avl_node_t *new_node, avl_cmp_t cmp)
{
	if (NULL == node)
	{
		node = new_node;

		return node;
	}
	else
	{
		sides_t side = (0 > cmp(new_node->data, node->data));

		node->children[side] = NodeInsert(node->children[side], new_node, cmp);

        return NodeBalance(node);
	}
}

avl_node_t *NodeRemove(avl_node_t *to_rm, const void *data, avl_cmp_t cmp)
{
    if (NULL == to_rm)
    {
        return NULL;
    }
    else
    {
        int res_cmp = cmp(to_rm->data, data);

        if (0 == res_cmp)
        {
            return NodeDelete(to_rm, cmp);
        }
        else
        {
            sides_t side = res_cmp > 0;

            to_rm->children[side] = NodeRemove(to_rm->children[side], data, cmp);

            return NodeBalance(to_rm);
        }
    }
}

/*          end recursive node API      */
/*          static functions            */

static avl_node_t *NodeDelete(avl_node_t *node, avl_cmp_t cmp)
{
    if (HAS_CHILD(node, RIGHT) && HAS_CHILD(node, LEFT))
    {
        avl_node_t *next_node = NextNode(node->children[RIGHT]);

        node->data = next_node->data;

        node->children[RIGHT] =
            NodeRemove(node->children[RIGHT], next_node->data, cmp);

        return node;
    }
    else
    {
        avl_node_t *save_branch = node->children[HAS_CHILD(node, RIGHT)];

        free(node);
        node = NULL;

        return save_branch;
    }
}

static avl_node_t *NextNode(avl_node_t *node)
{
    if (NULL == node->children[LEFT])
    {
        return node;
    }
    else
    {
        return NextNode(node->children[LEFT]);
    }
}

static avl_node_t *NodeBalance(avl_node_t *node)
{
    if (BRANCH_DIFF(node) > DIFF_TOLERANCE)
    {
        if (HAS_CHILD(node->children[RIGHT], RIGHT))
        {
            return LeftLeft(node);
        }
        else if (HAS_CHILD(node->children[RIGHT], LEFT))
        {
        	return LeftRight(node);
        }
    }
    else if (BRANCH_DIFF(node) < (-DIFF_TOLERANCE))
    {
        if (HAS_CHILD(node->children[LEFT], LEFT))
        {
            return RightRight(node);
        }
        else if (HAS_CHILD(node->children[LEFT], RIGHT))
        {
            return RightLeft(node);
        }
    }

    UPDATE_NODE_HEIGHT(node);

    return node;
}

static avl_node_t *NodeRotate(avl_node_t *root, sides_t side)
{
    avl_node_t *pivot = root->children[!side];

	root->children[!side] = pivot->children[side];
	pivot->children[side] = root;

    UPDATE_NODE_HEIGHT(root);
	UPDATE_NODE_HEIGHT(pivot);

    return pivot;
}

/* specific rotation functions, mainly for future LUT implementation */

static avl_node_t *RightRight(avl_node_t *node)
{
    return NodeRotate(node, RIGHT);
}

static avl_node_t *RightLeft(avl_node_t *node)
{
    node->children[LEFT] = NodeRotate(node->children[LEFT], LEFT);

    return NodeRotate(node, RIGHT);
}

static avl_node_t *LeftLeft(avl_node_t *node)
{
    return NodeRotate(node, LEFT);
}

static avl_node_t *LeftRight(avl_node_t *node)
{
    node->children[RIGHT] = NodeRotate(node->children[RIGHT], RIGHT);

    return NodeRotate(node, LEFT);
}

void *NodeGetData(avl_node_t *node)
{

	return node->data;
}
