/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Name: Daniel Jenudi
Reviewer: Ran 
Date: 10/03/2022
File: Data struct - Doubly Linked List
Description: header file
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/*******************************************************************************
                        Data struct - Doubly Linked List
********************************************************************************

Attributes and policy:
-   access any node in the list with running iterator 
-   iterator running foward and backward in the list 
-   Holds elements by reference
-	implement actions on node in the list with iterators.
-	EOL node place in the end of the list.
-   growth : can add node befor selected iterator, in the front of the list and
	in the back of the list. 
-------------------------------------------------------------------------------

Operations on DS:
- create DLL
- destroy DLL
- create iterator for the DLL nodes
- add or remove node to DLL
- get value of node with pointing iterator
- get the number of nodes in list 
- move iterator around the list
- get if list is empty
- change data in node with pointing iterator
- compare between two iterators
- splice two DLL's
- receive functions to search or change the list.


*******************************************************************************/

#ifndef __DLL_H__
#define __DLL_H__

#include <stddef.h>/* size_t */

/*******************************************************************************
                                 Typedefs
*******************************************************************************/

typedef struct DLL_list dll_list_t;
typedef struct DLL_node *dll_iterator_t;
typedef int (*is_match_func_t)(const void *data, void *parameter);
typedef int (*action_func_t)(void *data, void *parameter);

/*******************************************************************************
DLLCreate
Description: creates a new DLL
Return value:
	- in case of failure, will return null
Complexity: O(1) time
Notes: create EOL node ,that alwase be the last node, pointing to NULL and
store pointer to the DLL itself.
*******************************************************************************/
dll_list_t *DLLCreate(void);

/******************************************************************************
DLLDestroy
Description: destroy a DLL
Parameters: 
	- DLL
Complexity: O(n) time
*******************************************************************************/
void DLLDestroy(dll_list_t *list);

/*******************************************************************************
DLLCount
Description: return the number of node in a DLL
Parameters: 
	- DLL
Return value:
	- the number of elements in a DLL
Complexity: O(n) time 
*******************************************************************************/
size_t DLLCount(const dll_list_t *list);

/*******************************************************************************
DLLBegin
Description: returns an iterator to the first node in the list
Parameters: 
	- DLL
Return value:
	-  return iterator to the first node.
Complexity: O(1) time
*******************************************************************************/
dll_iterator_t DLLBegin(const dll_list_t *list);

/*******************************************************************************
DLLEnd
Description: returns an iterator to the last node in the list, the EOL node.
Parameters: 
	- linke list
Return value:
	-  return iterator to the last node.
Complexity: O(1) time, 
*******************************************************************************/
dll_iterator_t DLLEnd(const dll_list_t *list);

/*******************************************************************************
DLLNext
Description: return iterator to the next node.
Parameters: 
	- iterator
Return value:
	-  return iterator to the next node.
Complexity: O(1) time
Notes: undefined behavior for EOL node.
*******************************************************************************/
dll_iterator_t DLLNext(const dll_iterator_t iter);

/*******************************************************************************
DLLPrev
Description: return iterator to the previous node.
Parameters: 
	- iterator
Return value:
	-  return iterator to the previous node.
Complexity: O(1) time
Notes: undefined behavior for the first node in the list.
*******************************************************************************/
dll_iterator_t DLLPrev(const dll_iterator_t iter);

/*******************************************************************************
DLLGetData
Description: get node data
Parameters: 
	- iterator
Return value:
	- pointer to node data
Complexity: O(1) time
*******************************************************************************/
void *DLLGetData(const dll_iterator_t where);

/*******************************************************************************
DLLSetData
Description: set data in a node
Parameters: 
	- iterator
	- data pointer
Complexity: O(1) time, 
*******************************************************************************/
void DLLSetData(dll_iterator_t where, void *new_data);

/*******************************************************************************
DLLIsEmpty
Description: return if DLL is empty
Parameters: 
	- DLL
Return value:
	- return 1 if DLL is empty, else return 0
Complexity: O(1) time
*******************************************************************************/
int DLLIsEmpty(const dll_list_t *list);

/*******************************************************************************
DLLIsIterEqual
Description: return if two iterators are equal
Parameters: 
	- two iterators
Return value:
	- return 1 if equal, else return 0
Complexity: O(1) time
*******************************************************************************/
int DLLIsIterEqual(const dll_iterator_t iter1, const dll_iterator_t iter2);

/*******************************************************************************
DLLInsertBefore
Description: insert new node befor chosen iterator
Parameters: 
	- iterator
	- pointer to data
Return value:
	- iterator to the node with the new data
Complexity: O(1) time
*******************************************************************************/
dll_iterator_t DLLInsertBefore(dll_iterator_t where, void *data);

/*******************************************************************************
DLLPushFront
Description: insert new node befor the first node in the list
Parameters: 
	- DLL
	- pointer to data
Return value:
	- if allocation succeed return 0, else return 1.
Complexity: O(1) time
*******************************************************************************/
int DLLPushFront(dll_list_t *list, void *data); 

/*******************************************************************************
DLLPushBack
Description: insert new node befor the EOL node in the list
Parameters: 
	- DLL
	- pointer to data
Return value:
	- if allocation succeed return 0, else return 1.
Complexity: O(1) time
*******************************************************************************/
int DLLPushBack(dll_list_t *list, void *data); 

/*******************************************************************************
DLLRemove
Description: Removes node from a specific location
Parameters: 
	- iterator
Return value:
	- iterator to the next node
Complexity: O(1) time
Notes: undefined behavior for EOL node.
*******************************************************************************/
dll_iterator_t DLLRemove(dll_iterator_t iter);

/*******************************************************************************
DLLPopFront
Description: Remove the first node of a list.
Parameters: 
	- iterator
Return value:
	- the data of the node that has been removed
Complexity: O(1) time
*******************************************************************************/
void *DLLPopFront(dll_list_t *list); 

/*******************************************************************************
DLLPopBack
Description: Remove the last node of a list (before the EOL node).
Parameters: 
	- iterator
Return value:
	- the data of the node that has been removed
Complexity: O(1) time
*******************************************************************************/
void *DLLPopBack(dll_list_t *list); 

/*******************************************************************************
DLLFindMatch
Description: get function by user to serche in DLL between tow iterators
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
dll_iterator_t DLLFindMatch(is_match_func_t is_match, void *param, 
							const dll_iterator_t from, const dll_iterator_t to);
							
/*******************************************************************************
DLLMultiFind
Description: get function by user to serche in DLL between tow iterators and 
			 store the result in DLL
Parameters: 
	- iterators from and to
	- function
	- parametor to the function
	- DLL that will contain the result
Return value:
	- for partly success of allocation return the number of allocation that have
	  been made
	- for 0 success of allocation return -1
	- for successfuly operate on all range return 0 
Complexity: O(n) time
Notes: 'to' uninclude in the search
*******************************************************************************/
int DLLMultiFind(is_match_func_t is_match, void *param,
		         const dll_iterator_t from, const dll_iterator_t to,
		         dll_list_t *result);

/*******************************************************************************
DLLForEach
Description: get function by user for change DLL between tow iterators
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
Notes: to uninclude in the action function
*******************************************************************************/
int DLLForEach(action_func_t action_func, void *param, const dll_iterator_t from,
	           const dll_iterator_t to);
	           
/*******************************************************************************
DLLSplice
Description: move a range of nodes between two iterators from list 1,
 			 before dest iterator of list 2.   
Parameters: 
	- iterators from and to from list 1
	- iterator dest from list 2
Return value:
	- return the last iterator that have been moved 
Complexity: O(1) time
Notes: to uninclude in the search function, both lists will be vaild after the
	   opreation.
*******************************************************************************/
dll_iterator_t DLLSplice(dll_iterator_t dest, dll_iterator_t from,
						 dll_iterator_t to);

#endif /*__DLL_H__*/

