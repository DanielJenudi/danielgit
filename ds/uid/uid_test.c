/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Name: Daniel Jenudi
Reviewer: Schreiber
Date: 28/03/2022
File: Data struct - Uniqe ID
Description: test file
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/

#include <stdio.h>/* printf */
#include <unistd.h>/* sleep */

#include "uid.h"/* upi.h */

static void RunTest(int test);
int IntComper(int x, int y);

enum
{
	SUCCESS = 0,
	FAIL = 1
};

int main()
{
	ilrd_uid_t uid1 = UIDBadUID;
	ilrd_uid_t uid2 = UIDBadUID;
	ilrd_uid_t uid3 = UIDBadUID;
	
	printf("IsSame Check: ");
	RunTest(IntComper(UIDIsSame(uid1, UIDBadUID), 0));
	uid1 = UIDCreate();
	sleep(1);
	uid2 = UIDCreate();
	sleep(1);
	uid3 = UIDCreate();
	
	printf("udi1:\n");
	printf("%ld\n", uid1.time);
	printf("%d\n", uid1.pid);
	printf("%lu\n", uid1.counter);
	
	printf("\nudi2:\n");
	printf("%ld\n", uid2.time);
	printf("%d\n", uid2.pid);
	printf("%lu\n", uid2.counter);
	
	printf("\nudi3:\n");
	printf("%ld\n", uid3.time);
	printf("%d\n", uid3.pid);
	printf("%lu\n", uid3.counter);
	
	printf("\nIsSame Check: ");
	RunTest(IntComper(UIDIsSame(uid1, UIDBadUID), 1));
	
	return 0;
}

static void RunTest(int test)
{
	if (1 == test)
	{
		printf("\x1b[0;34m");
		printf("OK!\n\n");
		printf("\x1b[0m");
	}
	else
	{
		printf("\x1b[1;35m");
		printf("\nTest Failed!\n\n");
		printf("\x1b[0m");
	}
}

int IntComper(int x, int y)
{
	if(x != y)
	{
		return FAIL;
	}
	
	return SUCCESS;
}


