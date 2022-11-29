/*****************************************************************************
*Author: Daniel Jenudi														 *
*Reviewer: Ran          													 *
*Date: 25/05/2022															 *
*dhcp.h																	 *
******************************************************************************/

/*******************************************************************************
									DHCP	
********************************************************************************
Description: 
The Dynamic Host Configuration Protocol (DHCP) is a network management protocol.
used on Internet Protocol (IP) networks for automatically assigning IP addresses
and other communication parameters to devices connected to the network using a
client–server architecture.

Attributes and policy:
	- FIFO
	...

-------------------------------------------------------------------------------

Operations on DHCP:
	- Create
	- Destroy
	- AlocateIP
	- FreeIP
	- AvailableIPs

*******************************************************************************/
#ifndef __DHCP_H__
#define __DHCP_H__

#include <stddef.h> /* for size_t */

/*******************************************************************************
									Typedefs
*******************************************************************************/

typedef struct DHCP dhcp_t;

/*******************************************************************************
									Functions
*******************************************************************************/

dhcp_t *DHCPCreate(const char *network, size_t subnet);
/******************************************************************************
DHCPCreate
Description: Creates a new DHCP.
Parameters: 
	- network - a valid IPV4 address (end with 0).
	- subnet
Return value:
	- in case of success, returns pointer to the new DHCP.
	- in case of failure , returns NULL.
Time complexity: O(n).
Note: 
	- first and last 2 addresses are always set as allocated.
	- subnet in range 2 < subnet , else , undefined behavior occurs.
*****************************************************************************/

void DHCPDestroy(dhcp_t *dhcp);
/******************************************************************************
DHCPDestroy
Description: Destroys the given DHCP.
Parameters: 
	- DHCP - pointer to the DHCP.
Return value:
	- None
Time complexity: O(n).
Note:
*****************************************************************************/

int DHCPAllocIP(dhcp_t *dhcp , const char *requested_ip, char *res_ip);
/******************************************************************************
DHCPAllocIP
Description: Allocate a unique IP address.
Parameters: 
	- DHCP - pointer to the DHCP.
	- IP address request - Ip you want to get.
	- res_ip pointer to store the result ip granted by the function.
Return value:
	- in case of success, returns 0
	- in case of failure , returns non 0
Time complexity: O(logn).
Note: 
	- If requested_ip unvalid or already allocated, the lowest free address
	  is stored instead.
	- requested_ip has to be in Network ,  else , undefined behavior occurs.
	- requested_ip may be NULL if you dont have requested_ip.
	- In case DHCP is NULL, undefined behavior occurs.

*****************************************************************************/

void DHCPFreeIP(dhcp_t *dhcp, char *ip);
/******************************************************************************
DHCPFreeIP
Description: Frees an IP address.
Parameters: 
	- DHCP - pointer to the DHCP.
	- IP address to free.
Return value:
	- None
Time complexity: O(logn).
Note: 
 	- In case DHCP is NULL, undefined behavior occurs.
	- ip has to be in Network ,  else , undefined behavior occurs.
	- Ip can't be the first or 2 last ip's 
*****************************************************************************/

size_t DHCPAvailableIPs(const dhcp_t *dhcp);
/******************************************************************************
DHCPAvailableIPs
Description: Count the remaining available addresses.
Parameters: 
	- DHCP - pointer to the DHCP.
Return value:
	- Count of the remaining available addresses.
Time complexity: O(n).
Note:
*****************************************************************************/

void PrintTree(dhcp_t *dhcp);

#endif /* __DHCP_H__ */
