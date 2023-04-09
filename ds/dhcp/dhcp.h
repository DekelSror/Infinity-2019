/*==============================================================================
Data Structures - Doubly Linked List with iterators
Header
Dekel Sror
Review: Shon Weinberg
OL66
Version 1
==============================================================================*/
#ifndef __DHCP_H
#define __DHCP_H

#include <stddef.h> /* size_t */

typedef struct dhcp_s dhcp_t;

typedef enum
{
    success,
    system_failure,
    different_ip,
    full_capacity
} dhcp_status_t;

#define IP_BYTES (4)

/*
struct dhcp_s
{
        node_t root;
        size_t tree_height;
        unsigned char network_ip[4];
};

typedef struct node_s
{
        struct node_s *parent;
        struct node_s *children[2];
        int is_occupied;
} node_t;
*/


/*
Creates a new DHCP.

Arguments:
subnet mask.
network_ip.

Returnes a pointer to the DHCP, NULL on failure.

complexity O(1)
*/
dhcp_t *DHCPCreate(unsigned short subnet_mask, const unsigned char network_ip[IP_BYTES]);

/*
Destroy a given DHCP.

Arguments:
dhcp.

complexity O(n)
*/
void DHCPDestroy(dhcp_t *dhcp);

/*
Free a given IP address.

Arguments:
        dhcp: handle to dhcp.
        ip_to_free: IP address to free


complexity O(1)
*/
void DHCPFreeIP(dhcp_t *dhcp, const unsigned char ip_to_free[IP_BYTES]);

/*
Allocate a new IP address.

Arguments:
        dhcp.

request:
        Desired IP address. When  Adress differs from { 0, 0, 0, 0},
        the server will try to allocate requested address.
        if requested address is in use, an arbitary address will be
    put to ip_response.
        when request is { 0, 0, 0, 0}, an arbitary address wil be returned
response:
         buffer to store responded IP

Returns appropriate status

complexity O(1)
*/
dhcp_status_t DHCPAllocIP(dhcp_t *dhcp,
                                const unsigned char ip_request[IP_BYTES],
                                unsigned char ip_response[IP_BYTES]);

/*
Count avaliable IP addresses.

Arguments:
subnet mask.

Returnes a pointer to the DHCP, NULL on failure.

complexity O(n)
*/
size_t DHCPCountFree(const dhcp_t *dhcp);


#endif /* __DHCP_H */
