/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Name: Daniel Jenudi
Reviewer: Schreiber
Date: 28/03/2022
File: Data struct - Uniqe ID
Description: header file
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/*******************************************************************************
                        Data struct - UID
********************************************************************************

Attributes and policy:
- get uniqe ID to any UID's 
-------------------------------------------------------------------------------

Operations on DS:
- create UID
- compare between two UID
- get bad UID for initalize.

*******************************************************************************/

#ifndef __UID_H__
#define __UID_H__

#include <stddef.h>/* size_t */
#include <sys/types.h>/* pid_t */
#include <time.h>/* time_t */

/*******************************************************************************
                                 Typedefs
*******************************************************************************/

typedef struct 
{
	size_t counter;
	time_t time;
	pid_t pid;
} ilrd_uid_t;


/*******************************************************************************
bad_uid
Description: unviled UID for initialize
*******************************************************************************/
extern const ilrd_uid_t UIDBadUID;

/*******************************************************************************
UIDCreate
Description: creates a new UID
Return value:
	- new and uniqe UID, in case of failure return UIDBadUID.
Complexity: O(1) time
*******************************************************************************/
ilrd_uid_t UIDCreate(void);

/*******************************************************************************
UIDIsSame
Description: return if two UID are equal
Parameters: 
	- two UID's
Return value:
	- return 1 if equal, else return 0
Complexity: O(1) time
*******************************************************************************/
int UIDIsSame(ilrd_uid_t uid1, ilrd_uid_t uid2);

#endif /*__UID_H__*/


