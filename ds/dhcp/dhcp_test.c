/*****************************************************************************
*Author: Daniel Jenudi														 *
*Reviewer: Ran          													 *
*Date: 25/05/2022															 *
*dhcp test																	 *
******************************************************************************/

#include <stdio.h> /* for printf */
#include <string.h>
#include <stdlib.h>
#include "dhcp.h"

enum Status
{
	SUCCESS,
	FAIL
};

enum Bool
{
	FALSE,
	TRUE
};

#define RUNTEST(test) {\
            if (0 == test)\
            {\
                printf("\x1b[0;32m\x1b[1m\x1b[7m\x1b[5m");\
                printf("OK\n\n");\
                printf("\x1b[0m");\
            }\
            else\
            {\
                printf("\x1b[1;31m\x1b[1m\x1b[7m\x1b[5m");\
                printf("Test Failed\n\n");\
                printf("\x1b[0m");\
            }\
        }

void TestSubnet24();
void TestSubnet28();

int IntComper(int x, int y);
int StringComper(char *x, char *y);

int main()
{
    printf("~~~ alloc TestSubnet24 ~~~\n");
    TestSubnet24();
    /*printf("\n~~~ alloc TestSubnet28 ~~~\n");
    TestSubnet28();*/

	return 0;
}

void TestSubnet28()
{
        dhcp_t *dhcp = DHCPCreate("0.0.0.0", 28);
    char buffer[16] = {0};
    char *req1 = "0.0.0.9";
    char *req2 = "0.0.0.8";
    char *req3 = "0.0.0.0";
    char *req4 = "0.0.0.15";
    char *req5 = "0.0.0.14";
    char *req6 = "0.1.0.14";
    char *req7 = "0.0.0.16";

    printf("alloc request %s\n", req1);
    RUNTEST(IntComper(DHCPAllocIP(dhcp, req1, buffer), SUCCESS));
    RUNTEST(StringComper(buffer, req1));

    printf("alloc request %s\n", req2);
    RUNTEST(IntComper(DHCPAllocIP(dhcp, req2, buffer), SUCCESS));
    RUNTEST(StringComper(buffer, req2));

    printf("alloc request %s\n", req3);
    RUNTEST(IntComper(DHCPAllocIP(dhcp, req3, buffer), SUCCESS));
    RUNTEST(!StringComper(buffer, req3));

    printf("alloc request %s\n", req4);
    RUNTEST(IntComper(DHCPAllocIP(dhcp, req4, buffer), SUCCESS));
    RUNTEST(!StringComper(buffer, req4));

    printf("alloc request %s\n", req5);
    RUNTEST(IntComper(DHCPAllocIP(dhcp, req5, buffer), SUCCESS));
    RUNTEST(!StringComper(buffer, req5));

    printf("alloc request %s\n", req6);
    RUNTEST(IntComper(DHCPAllocIP(dhcp, req5, buffer), SUCCESS));
    RUNTEST(!StringComper(buffer, req5));

    printf("alloc request %s\n", req7);
    RUNTEST(IntComper(DHCPAllocIP(dhcp, req7, buffer), SUCCESS));
    RUNTEST(!StringComper(buffer, req5));

    printf("free ip:\n");
    RUNTEST(IntComper(DHCPAvailableIPs(dhcp), 6));

    printf("free and alloc request %s\n", req2);
    DHCPFreeIP(dhcp, req2);
    RUNTEST(IntComper(DHCPAllocIP(dhcp, req2, buffer), SUCCESS));
    RUNTEST(StringComper(buffer, req2));

    printf("free and alloc request %s\n", req1);
    DHCPFreeIP(dhcp, req1);
    RUNTEST(IntComper(DHCPAllocIP(dhcp, req1, buffer), SUCCESS));
    RUNTEST(StringComper(buffer, req1));

    PrintTree(dhcp);

    DHCPDestroy(dhcp);
}

void TestSubnet24()
{
    dhcp_t *dhcp = DHCPCreate("123.213.104.189", 24);
    char buffer[16] = {0};
    char req1[] = "123.213.104.189";
    char req2[] = "123.213.104.10";
    char req3[] = "123.213.104.0";
    char req4[] = "123.213.104.255";
    char req5[] = "123.213.104.254";

    printf("alloc request %s\n", req1);
    RUNTEST(IntComper(DHCPAllocIP(dhcp, req1, buffer), SUCCESS));
    RUNTEST(StringComper(buffer, req1));

    printf("alloc request %s\n", req2);
    RUNTEST(IntComper(DHCPAllocIP(dhcp, req2, buffer), SUCCESS));
    RUNTEST(StringComper(buffer, req2));

    printf("alloc request %s\n", req3);
    RUNTEST(IntComper(DHCPAllocIP(dhcp, req3, buffer), SUCCESS));
    RUNTEST(!StringComper(buffer, req3));

    printf("alloc request %s\n", req4);
    RUNTEST(IntComper(DHCPAllocIP(dhcp, req4, buffer), SUCCESS));
    RUNTEST(!StringComper(buffer, req4));
    
    printf("alloc request %s\n", req5);
    RUNTEST(IntComper(DHCPAllocIP(dhcp, req5, buffer), SUCCESS));
    RUNTEST(!StringComper(buffer, req5));

    printf("free ip:\n");
    RUNTEST(IntComper(DHCPAvailableIPs(dhcp), 248));
    
    printf("free and alloc request %s\n", req2);
    DHCPFreeIP(dhcp, req2);
    printf("free ip:\n");
    RUNTEST(IntComper(DHCPAvailableIPs(dhcp), 249));
    RUNTEST(IntComper(DHCPAllocIP(dhcp, req2, buffer), SUCCESS));
    RUNTEST(StringComper(buffer, req2));

    printf("free and alloc request %s\n", req1);
    DHCPFreeIP(dhcp, req1);
    printf("free ip:\n");
    RUNTEST(IntComper(DHCPAvailableIPs(dhcp), 249));
    RUNTEST(IntComper(DHCPAllocIP(dhcp, req1, buffer), SUCCESS));
    RUNTEST(StringComper(buffer, req1));

    /*PrintTree(dhcp);*/

    DHCPDestroy(dhcp);
}

int IntComper(int x, int y)
{
	if(x != y)
	{
		return FAIL;
	}
	
	return SUCCESS;
}

int StringComper(char *x, char *y)
{
	if(0 != strcmp(x, y))
	{
		return FAIL;
	}
	
	return SUCCESS;
}




