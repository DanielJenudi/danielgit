/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Name: Daniel Jenudi
Reviewer: Ran 
Date: 10/03/2022
File: Data struct - Singly linked list
Description: header file
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/*******************************************************************************
                        Data struct - link_list
********************************************************************************

Attributes and policy:
-   access any node in the list with running iterator 
-   iterator running only foword in the list 
-   Holds elements by reference
-   growth : can add node only befor selected iterator. after adding, the 
    selected iterator store the new data and point to the new node with the 
    original data
-------------------------------------------------------------------------------

Operations on DS:
- create linked_list
- destroy linked_list
- add node to the list
- create iterator  
- get value of node with pointing iterator
- get the number of nodes in list 
- move iterator to the beginning, ending and next node in a list
- get if list is empty
- change data in node with pointing iterator
- compare between two iterators

*******************************************************************************/

#ifndef __LINKE_LIST_H__
#define __LINKE_LIST_H__

#include <stddef.h> /* size_t */

/*******************************************************************************
                                 Typedefs
*******************************************************************************/

typedef struct s_linked_list s_linked_list_t;
typedef struct s_list_node s_list_node_t;
typedef struct s_list_node *iterator_t;
typedef int (*match_func_t)(const void *data, void *parameter);
typedef int (*action_func_t)(void *data, void *parameter);

/*******************************************************************************
SLinkedListCreate
Description: creates a new linked list
Return value:
	- in case of failure, will return null
Complexity: O(1) time
Notes: create dummy node ,that alwase be the last node, pointing to NULL and
store data pointer to NULL.
*******************************************************************************/
s_linked_list_t *SLinkedListCreate(void);

/******************************************************************************
SLinkedListDestroy
Description: destroy a linked list
Parameters: 
	- linked list
Complexity: O(n) time
*******************************************************************************/
void SLinkedListDestroy(s_linked_list_t *list);

/*******************************************************************************
SLinkedListCount
Description: return the number of node in a linked list
Parameters: 
	- linke list
Return value:
	- the number of elements in a linke list
Complexity: O(n) time 
*******************************************************************************/
size_t SLinkedListCount(const s_linked_list_t *list);

/*******************************************************************************
SLinkedListBegin
Description: returns an iterator to the first node in the list
Parameters: 
	- linke list
Return value:
	-  return iterator to the first node.
Complexity: O(1) time
*******************************************************************************/
iterator_t SLinkedListBegin(const s_linked_list_t *list);

/*******************************************************************************
SLinkedListEnd
Description: returns an iterator to the last node in the list, the dummy node.
Parameters: 
	- linke list
Return value:
	-  return iterator to the last node.
Complexity: O(1) time, 
*******************************************************************************/
iterator_t SLinkedListEnd(const s_linked_list_t *list);

/*******************************************************************************
SlinkedListNext
Description: return iterator to the next node.
Parameters: 
	- iterator
Return value:
	-  return iterator to the next node.
Complexity: O(1) time
*******************************************************************************/
iterator_t SlinkedListNext(const iterator_t iter);

/*******************************************************************************
SLinkedListGetData
Description: get pointer to node data
Parameters: 
	- iterator
Return value:
	- pointer to node data
Complexity: O(1) time
*******************************************************************************/
void *SLinkedListGetData(const iterator_t iter);

/*******************************************************************************
SLinkedListSetData
Description: set data pointer in node
Parameters: 
	- iterator
	- data pointer
Complexity: O(1) time, 
*******************************************************************************/
void SLinkedListSetData(iterator_t iter, const void *new_data);

/*******************************************************************************
SLinkedListIsEmpty
Description: return if linke list is empty
Parameters: 
	- linke lise
Return value:
	- return 1 if linke list is empty, else return 0
Complexity: O(1) time
*******************************************************************************/
int SLinkedListIsEmpty(const s_linked_list_t *list);

/*******************************************************************************
SLinkedListIsIterEqual
Description: return if two iterators are equal
Parameters: 
	- two iterators
Return value:
	- return 1 if equal, else return 0
Complexity: O(1) time
*******************************************************************************/
int SLinkedListIsIterEqual(const iterator_t iter1, const iterator_t iter2);

/*******************************************************************************
SLinkedListInsertBefore
Description: insert new node befor chosen iterator
Parameters: 
	- iterator
	-pointer to data
Return value:
	- iterator to the node with the new value
Complexity: O(1) time 
Notes: after adding, the selected iterator store the new data and point to the 
new node with the original data
*******************************************************************************/
iterator_t SLinkedListInsertBefore(iterator_t where, const void *data);

/*******************************************************************************
SLinkedListRemove
Description: Removes node from a specific location
Parameters: 
	- iterator
Return value:
	- iterator to the next node
Complexity: O(1) time
Notes: after remove, the selected iterator store the next node data and pointer.
the next iterator will be remove.
*******************************************************************************/
iterator_t SLinkedListRemove(iterator_t iter);

/*******************************************************************************
SLinkedListFind
Description: get function by user to serche in linke list between tow iterators
Parameters: 
	- iterators from and to
	- function
	- parametor to the function
Return value:
	- if succeed return iterator to the found location, else return the 
	iterator to
Complexity: O(n) time
Notes: to uninclude in the search function
*******************************************************************************/
iterator_t SLinkedListFind(match_func_t is_match, void *param, iterator_t from,
                           iterator_t to);

/*******************************************************************************
SLinkedListForEach
Description: get function by user for change linke list between tow iterators
Parameters: 
	- iterators from and to
	- function
	- parametor to the function
Return value:
	- if succeed return 0, else return 1 
Complexity: O(n) time
Notes: to uninclude in the search function
*******************************************************************************/
int SLinkedListForEach(action_func_t action_func, void *param, iterator_t from,
			iterator_t to);

/*******************************************************************************
SLinkedListAppend
Description: append two linked list together and returns the combain list
Parameters: 
	- two linked list
Return value:
	- linked list of the appended two linked lists
Complexity: O(1) time
Notes: list src will destroy
*******************************************************************************/
s_linked_list_t *SLinkedListAppend(s_linked_list_t *dest, s_linked_list_t *src);


#endif /*__LINKE_LIST_H__*/


