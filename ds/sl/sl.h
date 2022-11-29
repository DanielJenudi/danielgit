/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Name: Daniel Jenudi
Reviewer: adiya 
Date: 24/03/2022
File: Data struct - Sorted List
Description: header file
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/*******************************************************************************
		 _____            _           _     _     _     _   
		/  ___|          | |         | |   | |   (_)   | |  
		\ `--.  ___  _ __| |_ ___  __| |   | |    _ ___| |_ 
		 `--. \/ _ \| '__| __/ _ \/ _` |   | |   | / __| __|
		/\__/ / (_) | |  | ||  __/ (_| |   | |___| \__ \ |_ 
		\____/ \___/|_|   \__\___|\__,_|   \_____/_|___/\__|
********************************************************************************

Attributes and policy:
-   access any node in the list with running iterator 
-   iterator running foward and backward in the list 
-   Holds elements by reference
-	implement actions on node in the list with iterators.
-	EOL node place in the end of the list.
-	the list is sorted with user comper function policy.
-   growth : can add node to the list, the node putted in the right place 
	by the program. 
	
-	compare function policy:
	compare function define the order of elements according to:
    if new data should be after, then  |cmp < 0| (negativ result)
    if new data should be first, then  |cmp > 0| (positive result)
    if equals new data should be after |cmp = 0| (equal result)

-------------------------------------------------------------------------------

Operations on DS:
- create SL
- destroy SL
- create iterator for the SL nodes
- add or remove node to SL
- get value of node with pointing iterator
- get the number of nodes in list 
- move iterator around the list
- get if list is empty
- change data in node with pointing iterator
- compare between two iterators
- merge two SL's
- receive functions to search or change the list.

*******************************************************************************/

#ifndef __SORTED_LINKED_LIST_H__
#define __SORTED_LINKED_LIST_H__

#include <stddef.h>/* size_t */
#include "/home/daniel/git/ds/dll/dll.h" /*dll.h*/

/*******************************************************************************
                                 Typedefs
*******************************************************************************/

typedef struct sl sl_t;
typedef dll_iterator_t sl_iterator_t;
typedef int (*sl_cmp_func_t)(const void *new_data, const void *list_data, 
			 void *param);
typedef int (*sl_is_match_func_t)(const void *data, void *param);
typedef int (*sl_action_func_t)(void *data, void *param);

/*******************************************************************************
SLCreate
Description: creates a new SL
Parameters: 
	- comper function
	- param
Return value:
	- in case of failure, will return null
Complexity: O(1) time
Notes: create EOL node ,that alwase be the last node, pointing to NULL and
store pointer to the SL itself. 
*******************************************************************************/
sl_t *SLCreate(sl_cmp_func_t cmp_func, void *param);

/******************************************************************************
SLDestroy
Description: destroy a SL
Parameters: 
	- SL
Complexity: O(n) time
*******************************************************************************/
void SLDestroy(sl_t *list);

/*******************************************************************************
SLInsert
Description: insert new node with comper function policy.
Parameters: 
	- SL
	- pointer to data
Return value:
	- iterator to the node with the new data
Complexity: O(1) time
*******************************************************************************/
sl_iterator_t SLInsert(sl_t *list, void *data);

/*******************************************************************************
SLRemove
Description: Removes node from a specific location
Parameters: 
	- iterator
Return value:
	- iterator to the next node
Complexity: O(1) time
Notes: undefined behavior for EOL node.
*******************************************************************************/
sl_iterator_t SLRemove(sl_iterator_t where);

/*******************************************************************************
SLPopFront
Description: Remove the first node of a list.
Parameters: 
	- iterator
Return value:
	- the data of the node that has been removed
Complexity: O(1) time
*******************************************************************************/
void *SLPopFront(sl_t *list);

/*******************************************************************************
SLPopBack
Description: Remove the last node of a list (before the EOL node).
Parameters: 
	- iterator
Return value:
	- the data of the node that has been removed
Complexity: O(1) time
*******************************************************************************/
void *SLPopBack(sl_t *list);

/*******************************************************************************
SLBegin
Description: returns an iterator to the first node in the list
Parameters: 
	- SL
Return value:
	-  return iterator to the first node.
Complexity: O(1) time
*******************************************************************************/
sl_iterator_t SLBegin(const sl_t *list);

/*******************************************************************************
SLEnd
Description: returns an iterator to the last node in the list, the EOL node.
Parameters: 
	- SL
Return value:
	-  return iterator to the last node.
Complexity: O(1) time, 
*******************************************************************************/
sl_iterator_t SLEnd(const sl_t *list);

/*******************************************************************************
SLNext
Description: return iterator to the next node.
Parameters: 
	- iterator
Return value:
	-  return iterator to the next node.
Complexity: O(1) time
Notes: undefined behavior for EOL node.
*******************************************************************************/
sl_iterator_t SLNext(const sl_iterator_t iter);

/*******************************************************************************
SLPrev
Description: return iterator to the previous node.
Parameters: 
	- iterator
Return value:
	-  return iterator to the previous node.
Complexity: O(1) time
Notes: undefined behavior for the first node in the list.
*******************************************************************************/
sl_iterator_t SLPrev(const sl_iterator_t iter);


/*******************************************************************************
SLIsIterEqual
Description: return if two iterators are equal
Parameters: 
	- two iterators
Return value:
	- return 1 if equal, else return 0
Complexity: O(1) time
*******************************************************************************/
int SLIsIterEqual(const sl_iterator_t iter1, const sl_iterator_t iter2);

/*******************************************************************************
SLGetData
Description: get node data
Parameters: 
	- iterator
Return value:
	- pointer to node data
Complexity: O(1) time
*******************************************************************************/
void *SLGetData(const sl_iterator_t iter);

/*******************************************************************************
SLIsEmpty
Description: return if SL is empty
Parameters: 
	- SL
Return value:
	- return 1 if DLL is empty, else return 0
Complexity: O(1) time
*******************************************************************************/
int SLIsEmpty(const sl_t *list);

/*******************************************************************************
SLCount
Description: return the number of node in a SL
Parameters: 
	- SL
Return value:
	- the number of elements in a SL
Complexity: O(n) time 
*******************************************************************************/
size_t SLCount(const sl_t *list);

/*******************************************************************************
SLFind
Description: Search in SL for data with list comper function. 
	- iterators from and to
	- list
	- parametor to the function
Return value:
	- if succeed return iterator to the found location, else return the 
	iterator 'to'
Complexity: O(n) time
Notes: 'to' uninclude in the search
*******************************************************************************/
sl_iterator_t SLFind(const sl_t *list, const sl_iterator_t from,
 					 const sl_iterator_t to, const void *data);
							

/*******************************************************************************
SLFindIf
Description: get function by user to serche in SL between tow iterators
Parameters: 
	- iterators from and to
	- function
	- parametor to the function
Return value:
	- if succeed return iterator to the found location, else return the 
	iterator 'to'
Complexity: O(n) time
Notes: 'to' uninclude in the search
*******************************************************************************/
sl_iterator_t SLFindIf(sl_is_match_func_t is_match, void *param, 
					   const sl_iterator_t from, const sl_iterator_t to);
					   
/*******************************************************************************
SLForEach
Description: get function by user for change SL between tow iterators
Parameters: 
	- iterators from and to
	- function
	- parametor to the function
Return value:
	- for partly success action of action_func return the number of action that
 	  have been made
	- for 0 success action of action_func return -1
	- for successfuly operate on all range return 0 
Complexity: O(n) time
Notes: 'to' uninclude in the action function. 
			be aware that changing the list values to be unsorted is undefine.
*******************************************************************************/
int SLForEach(sl_action_func_t action_func, void *param, 
			  const sl_iterator_t from, const sl_iterator_t to);
	           
/*******************************************************************************
SLMerge
Description: merge tow lists to dest list with comper function policy.
Parameters: 
	- list dest
	- list src
Return value:
	- return list dest 
Complexity: O(1) time
Notes: merging two lists with different compiler function policy is undefine. 
	   in the end of the process list src will be valid and empty.
*******************************************************************************/
sl_t *SLMerge(sl_t *dest, sl_t *src);


#endif /* __SORTED_LINKED_LIST_H__ */



