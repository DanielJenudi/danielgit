/*******************************************************************************
 Author: daniel jenudi 
 Date: 28/04/2022
 Reviewed By: noam
*******************************************************************************/

/*******************************************************************************
                                BST
********************************************************************************
text 

Attributes and policy:
- profom quick apllication to data 
- sort data with compar function
- contain EOT element in the end of BST
- travel BST with iterators

-------------------------------------------------------------------------------

Operations on BST:
- creat and distroy BST
- insert and remove data
- find data in BST
- travel BST with iterators
- go next or prev element
- count the number of elements in BST
- check if BST is empty
- implement action function on range of iterators
- compare iterators
- get data from iterator

*******************************************************************************/

#ifndef __BST_H__
#define __BST_H__

#include <stddef.h>

/*******************************************************************************
                                 Typedefs
*******************************************************************************/

typedef struct bst bst_t;
typedef struct bst_node *bst_iter_t;
typedef int (*bst_cmp_func_t)(const void *new_data, const void *tree_data, void *param);
/* return val of 0 invokes undefined behavior,
cmp func: 1 new data is bigger (RIGHT), -1 smaller (LEFT), 0 failure (we have it allready- mention undefined behaviour */

typedef int (*bst_action_func_t)(void *data, void *param); 
/*action func returns: 0 success (all)
non zero failure, exit after first failure
pay attention to the arguments order..*/


/*******************************************************************************
BSTCreate
Description: creat new BST
Parameters: 
	- compare function
	-param
Return value:
	- new BST
Complexity: O(1)
Notes: cmp determine the order of data inside BST
	  
*******************************************************************************/
bst_t *BSTCreate(bst_cmp_func_t cmp, void *param); 



/*******************************************************************************
BSTDestroy
Description: distroy BST
Parameters: 
	- BST
Complexity: O(n), worst case O(n^2) 
Notes: 
	  
*******************************************************************************/
void BSTDestroy(bst_t *bst);



/*******************************************************************************
BSTInsert
Description: 
Parameters: 
	- BST
	- data
Return value:
	- iterator to the data
Complexity: O(log(n)), worst case O(n) 
Notes: if fail return NULL, inserting existing values may result in undefined 
	   behavior.
	  
*******************************************************************************/
bst_iter_t BSTInsert(bst_t *bst, void *data);



/*******************************************************************************
BSTRemove
Description: remove data from BST
Parameters: 
	- iterator 
Complexity: O(n)
Notes: BST will remain sorted, remove EOT result in undefined behavior.
	  
*******************************************************************************/
void BSTRemove(bst_iter_t iter);



/*******************************************************************************
BSTBegin
Description: return iterator to the first value via compare function 
Parameters: 
	- BST
Return value:
	- iterator to the first value
Complexity: O(n)
	  
*******************************************************************************/
bst_iter_t BSTBegin(bst_t *bst);



/*******************************************************************************
BSTEnd
Description: return iterator to the EOT.
Parameters: 
	- BST
Return value:
	- iterator to the EOT
Complexity: O(1) 
Notes: return EOT
	  
*******************************************************************************/
bst_iter_t BSTEnd(bst_t *bst);



/*******************************************************************************
BSTNext
Description: return iterator to the next data (in compare function policy)
Parameters: 
	- iterator
Return value:
	- iterator
Complexity: O(n)
Notes: oprate BSTNext to the the EOT result in undefined behavior
	  
*******************************************************************************/
bst_iter_t BSTNext(bst_iter_t iter);



/*******************************************************************************
BSTPrev
Description: return iterator to the previos data (in compare function policy)
Parameters: 
	- iterator
Return value:
	- iterator
Complexity: 
Notes:  oprate BSTPrev to the the smallest value result in undefined behavior
	  
*******************************************************************************/
bst_iter_t BSTPrev(bst_iter_t iter);



/*******************************************************************************
BSTFind
Description: find data between two iterators
Parameters: 
	- BST
	- iterator from
	- iterator to
	- data
Return value:
	- iterator to the data
Complexity: O(n^2) 
Notes: if data doesn't exist, return the iterator to 
	  
*******************************************************************************/
bst_iter_t BSTFind(bst_t *bst, bst_iter_t from, bst_iter_t to, void *data);



/*******************************************************************************
BSTGetData
Description: get data from iterator 
Parameters: 
	- iterator
Return value:
	- data
Complexity: O(1) 
	  
*******************************************************************************/
void *BSTGetData(bst_iter_t iter);




/*******************************************************************************
BSTCount
Description: count the number of elements in BST
Parameters: 
	- BST
Return value:
	- the number of elements in BST
Complexity: O(n^2)
	  
*******************************************************************************/
size_t BSTCount(const bst_t *bst);



/*******************************************************************************
BSTIsEmpty
Description: check if BST is empty
Parameters: 
	- BST
Return value:
	- TRUE\FALS
Complexity: O(1)
	  
*******************************************************************************/
int BSTIsEmpty(const bst_t *bst);



/*******************************************************************************
BSTIterIsEqual
Description: check if two iterators are the same
Parameters: 
	- two iterators
Return value:
	- TRUE\FALS
Complexity: O(1)
	  
*******************************************************************************/
int BSTIterIsEqual(bst_iter_t iter1, bst_iter_t iter2);



/*******************************************************************************
BSTForeach
Description: oprate action on all elemnts between two iterators.
Parameters: 
	- iterator from
	- iterator to
	- action function
	- parameter for action function
Return value:
	- if action function fail return FAIL else return SUCCES
Complexity: O(n^2)
Notes: data modification may result in undefined behavior. if action function
	   fail, BSTForeach stop imidiatly.
	  
*******************************************************************************/
int BSTForeach(bst_iter_t from, bst_iter_t to, bst_action_func_t act_func, void *param);



#endif /*__BST_H__*/

