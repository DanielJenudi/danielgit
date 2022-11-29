/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Name: Daniel Jenudi
Reviewer: Schreiber
Date: 28/03/2022
File: Data struct - Uniqe ID
Description: source file
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
#include <unistd.h>/* getpid */

#include "uid.h" /* upi.h */

#define TIMEFAIL -1

const ilrd_uid_t UIDBadUID = {0, 0, 0};

ilrd_uid_t UIDCreate(void)
{
	ilrd_uid_t uid = UIDBadUID;
	static size_t counter = 0;

	uid.time = time(NULL);
	if (TIMEFAIL == uid.time)
	{
		return UIDBadUID;
	}

	uid.pid = getpid();

	uid.counter = __sync_add_and_fetch(&counter, 1);

	return uid;
}

int UIDIsSame(ilrd_uid_t uid1, ilrd_uid_t uid2)
{
	int result = 0;

	result += (uid1.time == uid2.time);
	result += (uid1.pid == uid2.pid);
	result += (uid1.counter == uid2.counter);

	return (3 == result);
}
