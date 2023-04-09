/*==============================================================================
Data Structures - AVL Tree
Recursive node API
Dekel Sror
Review - Shon Weinberg
RC 1
==============================================================================*/

#ifndef AVL_NODE_H_
#define AVL_NODE_H_

#include "avl.h" /* avl_cmp_t, avl_op_t */

typedef struct avl_node_s avl_node_t;
typedef enum sides_e { LEFT, RIGHT } sides_t;

avl_node_t *NodeCreate(void *data);
avl_node_t *NodeInsert(avl_node_t *node, avl_node_t *new_node, avl_cmp_t cmp);
avl_node_t *NodeRemove(avl_node_t *to_rm, const void *data, avl_cmp_t cmp);
void NodeFreeAll 	  (avl_node_t *node);

avl_node_t *NodeFind  (avl_node_t *node, avl_cmp_t cmp, const void *data);
int NodeForEach 	  (avl_node_t *node, avl_op_t op, void *arg);
size_t NodeHeight 	  (avl_node_t *node);
size_t NodeCount 	  (avl_node_t *node);
void *NodeGetData     (avl_node_t *node);

#endif /* AVL_NODE_H_ */
