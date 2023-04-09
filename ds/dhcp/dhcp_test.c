/*==============================================================================
Data Structures - Doubly Linked List with iterators
Tests
Dekel Sror
Review: Shon Weinberg
OL66
Version 1
==============================================================================*/
#include <string.h> /* memcmp 			 */
#include <stdio.h>  /* printf  			 */

#include "dhcp.h"  /* dhcp API and types */

#define TEST_SIZE (8)

static void TestAllocNoSpecific(void);
static void TestCountFree(dhcp_t *dhcp, size_t exp_res);
static void TestAllocFreeSpecific(void);
/*  ========================================================================  */

int main(void)
{

	printf("TestAllocNoSpecific\n");
	TestAllocNoSpecific();

	printf("TestAllocFreeSpecific\n");
	TestAllocFreeSpecific();

	return 0;
}
/*  ========================================================================  */

static void TestAllocNoSpecific(void)
{
	unsigned char test_ip[4] = { 77, 77, 77, 0 };
	const unsigned char test_nw[4] = { 101, 101, 101, 0 };
	unsigned char res[4] = { 0 };
	size_t i = 0;

	dhcp_t *test = DHCPCreate(32 - TEST_SIZE, test_nw);
	dhcp_status_t test_alloc = success;

	for (i = 0; i < (1u << TEST_SIZE) - 3; ++i)
	{
		TestCountFree(test, (1u << TEST_SIZE) - (3 + i));
		test_alloc = DHCPAllocIP(test, test_ip, res);

		if (different_ip != test_alloc)
		{
			printf("address [%lu] is supposed to be occupied\n", i);
		}
	}

	TestCountFree(test, 0);
	DHCPDestroy(test);
}

void TestCountFree(dhcp_t *dhcp, size_t exp_res)
{
	size_t res = DHCPCountFree(dhcp);

	if (exp_res != res)
	{
		printf("count failed. exp_res %lu, had %lu\n", exp_res, res);
	}
}

static void TestAllocFreeSpecific(void)
{
	unsigned char test_ip[4] = { 77, 77, 77, 1 };
	const unsigned char test_nw[4] = { 0x55, 0x55, 0, 0 };
	unsigned char res[4] = { 0 };
	size_t i = 0;

	dhcp_t *test = DHCPCreate(32 - TEST_SIZE, test_nw);
	dhcp_status_t test_alloc = success;

	for (i = 0; i < (1u << TEST_SIZE) - 3; ++i)
	{
		TestCountFree(test, (1 << TEST_SIZE) - (3 + i));

		test_alloc = DHCPAllocIP(test, test_ip, res);

		if (success != test_alloc)
		{
			size_t index = 0;

			printf("address %d is not supposed to be occupied, status %d\n"
					, test_ip[3], test_alloc);

			printf("\nrequest: ");
			for (index = 0; index < IP_BYTES; ++index)
			{
				printf("[%d]", test_ip[index]);
			}

			printf("\nresponse: ");

			for (index = 0; index < IP_BYTES; ++index)
			{
				printf("[%d]", res[index]);
			}

			printf("\n");
		}

		++test_ip[3];
	}

	test_alloc = DHCPAllocIP(test, test_ip, res);

	if (full_capacity != test_alloc)
	{
		printf("alloc'd on a full_capacity server...\n");
	}

	for (i = 0; i < (1u << TEST_SIZE); ++i)
	{
		test_ip[3] = i;
		TestCountFree(test, i);
		DHCPFreeIP(test, test_ip);
	}

	TestCountFree(test, (1u << TEST_SIZE));

	DHCPDestroy(test);
}
