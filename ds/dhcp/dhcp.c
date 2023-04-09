/*==============================================================================
Data Structures - DHCP server with TRIE
Module
Dekel Sror
Review: Shon Weinberg
OL66
Version 1
==============================================================================*/
#include <stdlib.h> /* malloc, free 		 */
#include <assert.h> /* assert 				 */

#include "dhcp.h"   /* dhcp_t, dhcp_status_t */

/* number of reserved ip addresses */
#define NUM_META_DATA_IP (3)
#define BITS_IN_BYTE (8u)

typedef enum sides_e { LEFT, RIGHT, NUM_CHILDREN } sides_t;

typedef struct node_s
{
	struct node_s *parent;
	struct node_s *children[NUM_CHILDREN];
	int is_occupied;
} node_t;

struct dhcp_s
{
        node_t root;
        size_t tree_height;
        unsigned int network_ip;
};

/* reserved addresses */
static const unsigned char meta_data_addresses[NUM_META_DATA_IP][IP_BYTES] =
{
	{ 0, 0, 0, 0 }, /* network */
	{ 255, 255, 255, 255 }, /* broadcast */
	{ 255, 255, 255, 254 } /* dhcp */
};

/*  static functions - forward declaratins  */
/*  ========================================================================  */
static dhcp_status_t AllocIpIMP(node_t *node,
								size_t height,
								unsigned int req_buf,
								unsigned int *res_buf);

static void MaskRequetIp (dhcp_t *dhcp,
						  unsigned int network_ip,
						  unsigned int *host_ip);

static unsigned int IpToUint(const unsigned char ip_address[IP_BYTES]);
static void UintToIp(unsigned int buffer, unsigned char ip_address[IP_BYTES]);
static node_t *NodeCreate(node_t *parent);
static void UpdateIsOccupied(node_t *node);
static void NodeFreeExcess(node_t *node);
static void NodeDestory(node_t *node);
static size_t NodeCount(const node_t *node, size_t height);
/*  ========================================================================  */
/* dhcp API function definitoins */
dhcp_t *DHCPCreate (unsigned short subnet_mask,
					const unsigned char network_ip[IP_BYTES])
{
	dhcp_t *new_dhcp = malloc(sizeof(dhcp_t));
	dhcp_status_t meta_data_status = success;
	size_t i = 0;
	unsigned char alloc_res[4] = { 0 };

	assert(network_ip);

	if (NULL == new_dhcp)
	{
		return NULL;
	}

	new_dhcp->tree_height = IP_BYTES * BITS_IN_BYTE - subnet_mask;
	new_dhcp->root.parent = NULL;
	new_dhcp->root.children[LEFT] = NULL;
	new_dhcp->root.children[RIGHT] = NULL;
	new_dhcp->root.is_occupied = 0;
	new_dhcp->network_ip =  IpToUint(network_ip);

	/* allocate reserved addresses */
	for (i = 0; i < NUM_META_DATA_IP; ++i)
	{
		meta_data_status = DHCPAllocIP(new_dhcp,
								meta_data_addresses[i], alloc_res);

		if (success != meta_data_status)
		{
			DHCPDestroy(new_dhcp);
			new_dhcp = NULL;

			return NULL;
		}
	}

	return new_dhcp;
}

dhcp_status_t DHCPAllocIP(dhcp_t *dhcp,
						  const unsigned char ip_request[IP_BYTES],
						  unsigned char ip_response[IP_BYTES])
{
	unsigned int req_buf = 0u;
	unsigned int res_buf = 0u;
	dhcp_status_t status = full_capacity;

	assert(dhcp);
	assert(ip_request);
	assert(ip_response);

	req_buf = IpToUint(ip_request);
	/* override excess bits given by user with network_ip */
	MaskRequetIp(dhcp, dhcp->network_ip, &req_buf);

	if (!dhcp->root.is_occupied)
	{
		status = AllocIpIMP (&dhcp->root,
						dhcp->tree_height,
						req_buf,
						&res_buf);

		/* write network_ip to result ip */
		MaskRequetIp(dhcp, dhcp->network_ip, &res_buf);
		UintToIp(res_buf, ip_response);
	}

	if (success != status)
	{
		return status;
	}

	if (req_buf != res_buf)
	{
		return different_ip;
	}

	return success;

}

void DHCPDestroy(dhcp_t *dhcp)
{
	NodeDestory(dhcp->root.children[LEFT]);
	NodeDestory(dhcp->root.children[RIGHT]);

	dhcp->root.children[LEFT] = NULL;
	dhcp->root.children[RIGHT] = NULL;

	free(dhcp);

	dhcp = NULL;
}

void DHCPFreeIP(dhcp_t *dhcp,
				const unsigned char ip_to_free[IP_BYTES])
{
	unsigned int i = 0u;
	unsigned int req_buf = 0u;
	node_t *node = NULL;
	sides_t side = 0;

	assert(dhcp);
	assert(ip_to_free);

	node = &dhcp->root;
	req_buf = IpToUint(ip_to_free);
	dhcp->root.is_occupied = 0;

	for (i = dhcp->tree_height; 0 < i; --i)
	{
		/* get side using current bit index  */
		side = (req_buf >> (i - 1)) & 1u;

		if (NULL == node->children[side])
		{
			return;
		}

		node = node->children[side];
	}

	NodeFreeExcess(node);
}

size_t DHCPCountFree(const dhcp_t *dhcp)
{
	size_t address_space = 0u;
	assert(dhcp);

	/* address_space is 2 ^ height */
	address_space = 1u << (dhcp->tree_height);

	return address_space - NodeCount(&dhcp->root, dhcp->tree_height);
}

/*  end dhcp API  */
/*  ========================================================================  */
/*  static function definitoins  */

static dhcp_status_t AllocIpIMP (node_t *node,
							size_t height,
							unsigned int req_buf,
							unsigned int *res_buf)
{
	/* get side using current bit index  */
	sides_t side = (req_buf >> (height - 1)) & 1u;
	dhcp_status_t status = success;

	if ((0 == height))
	{
		node->is_occupied = 1;

		return success;
	}

	if (NULL != node->children[side] && node->children[side]->is_occupied)
	{
		side = !side;
	}

	if (NULL == node->children[side])
	{
		node->children[side] = NodeCreate(node);

		if (NULL == node->children[side])
		{
			NodeFreeExcess(node);

			return system_failure;
		}
	}

	/* set bit to (side) on result buffer */
	*res_buf <<= 1u;
	*res_buf |= side;

	status = AllocIpIMP(node->children[side], height - 1, req_buf, res_buf);

	if (system_failure != status)
	{
		UpdateIsOccupied(node);
	}

	return status;
}

static void NodeFreeExcess(node_t *node)
{
	node_t *parent_node = NULL;

	if (NULL == node->parent)
	{
		return;
	}

	parent_node = node->parent;

	if ((NULL == node->children[LEFT]) && (NULL == node->children[RIGHT]))
	{
		sides_t child_side = (node == parent_node->children[RIGHT]);

		node->parent = NULL;
		parent_node->children[child_side] = NULL;

		free(node);
		node = NULL;
	}
	else
	{
		node->is_occupied = 0;
	}
	NodeFreeExcess(parent_node);
}

static size_t NodeCount(const node_t *node, size_t height)
{
	if (NULL == node)
	{
		return 0;
	}

	if (node->is_occupied)
	{
		/* address_space is 2 ^ height */
		return (1u << (height));
	}

	return (NodeCount(node->children[LEFT],  height - 1) +
			NodeCount(node->children[RIGHT], height - 1));
}

static void NodeDestory(node_t *node)
{
	if (NULL == node)
	{
		return;
	}

	NodeDestory(node->children[LEFT]);
	NodeDestory(node->children[RIGHT]);

	node->children[LEFT] = NULL;
	node->children[RIGHT] = NULL;
	node->parent = NULL;

	free(node);

	node = NULL;
}

static void UpdateIsOccupied(node_t *node)
{
	/* both children are valid and occupied */
	if (NULL != node)
	{
		node->is_occupied = ((NULL != node->children[RIGHT]) &&
							 (NULL != node->children[LEFT]) &&
							 (node->children[RIGHT]->is_occupied) &&
							 (node->children[LEFT]->is_occupied));
	}
}

static node_t *NodeCreate(node_t *parent)
{
	node_t *new_node = malloc(sizeof(node_t));

	if (NULL != new_node)
	{
		new_node->parent = parent;
		new_node->children[LEFT] = NULL;
		new_node->children[RIGHT] = NULL;
		new_node->is_occupied = 0;
	}

	return new_node;
}

static void MaskRequetIp (dhcp_t *dhcp,
						  unsigned int network_ip,
						  unsigned int *host_ip)
{
	unsigned int mask = 0;
	size_t i = 0;

	for (i = 0; i < dhcp->tree_height; ++i)
	{
		mask <<= 1;
		++mask;
	}

	network_ip &= (~mask);
	*host_ip &= mask;
	*host_ip |= network_ip;
}

/* conversion functions - from array of uchars to uint and vice versa */
static void UintToIp(unsigned int buffer, unsigned char ip_address[IP_BYTES])
{
	ip_address[0] = ((buffer >> BITS_IN_BYTE * 3));
	ip_address[1] = ((buffer >> BITS_IN_BYTE * 2));
	ip_address[2] = ((buffer >> BITS_IN_BYTE));
	ip_address[3] = ((buffer));
}

static unsigned int IpToUint(const unsigned char ip_address[IP_BYTES])
{
	unsigned int buffer = 0;

	buffer |= ip_address[0];
	buffer <<= BITS_IN_BYTE;
	buffer |= ip_address[1];
	buffer <<= BITS_IN_BYTE;
	buffer |= ip_address[2];
	buffer <<= BITS_IN_BYTE;
	buffer |= ip_address[3];

	return buffer;
}
