/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Name: Daniel Jenudi
Reviewer: Ran
Date: 15/05/2022
File: Calculate
Description: Header file
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*******************************************************************************
 													
									" I'm Balanced BABY!!!!!!! "             

												              * *    
												           *    *  *
												      *  *    *     *  *
												     *     *    *  *    *
												 * *   *    *    *    *   *
		 █████╗ ██╗   ██╗██╗     				 *     *  *    * * .#  *   *
		██╔══██╗██║   ██║██║     				 *   *     * #.  .# *   *
		███████║██║   ██║██║     				  *     "#.  #: #" * *    *
		██╔══██║╚██╗ ██╔╝██║     				 *   * * "#. ##"       *
		██║  ██║ ╚████╔╝ ███████╗				   *       "###
		╚═╝  ╚═╝  ╚═══╝  ╚══════╝				             "##
															  "##		
(named after inventors Adelson-Velsky and Landis)			   ##.
												              .##:
												              :###
												              ;###
												            ,####.
********************************************************************************

Author: 
Date: 
Reviewed By: 

********************************************************************************
DESCRIPTION
AVL tree is a self-balancing Binary Search Tree (BST) where the difference 
between heights of left and right subtrees cannot be more than one for all 
nodes. 

REMINDER: The height of a node is the length of the longest downward path to a 
leaf from that node. The height of the root is the height of the tree.

Attributes and policy:
* Balance factor - In a binary tree the balance factor of a node X is defined to 
				   be the height difference.


--------------------------------------------------------------------------------

Operations on AVL:
- insert data to AVL.
- remove data from AVL
- get the height of the root data
- get if AVL is empty
- count the number of data's in AVL


*******************************************************************************/

#ifndef __AVL_H__
#define __AVL_H__

#include <stddef.h> /* size_t */

/*******************************************************************************
                                 Typedefs
*******************************************************************************/
enum order_type
{
    PRE = 0,
    IN = 1,
    POST = 2
};

typedef int (*avl_cmp_func_t)(const void *new_data, const void *tree_data,
							  void *param);
/* Compare Function
Return values:
- (0) : new_data is same as tree_data. Will cause undefined behaviour
- (0<): new_data is greater than tree_data
- (0>): new_data is less than tree_data
*/
typedef int (*avl_action_func_t)(void *data, void *param); 
/*Return Values:
- (0): Success for all
- Non zero value: Failure.
*/
typedef struct avl avl_t;


/*******************************************************************************
                                 Struct (in c file)
*******************************************************************************/


void AVLPrintAscending(avl_t *avl);
void AVLPrint(avl_t *avl);
void PrintTree(avl_t *avl);

/*******************************************************************************
                                 Operations
*******************************************************************************/
/*******************************************************************************
AVLCreate
Time Complexity: O(1)
Description: 
*******************************************************************************/
avl_t *AVLCreate(avl_cmp_func_t cmp, void *param);

/*******************************************************************************
AVLDestory
Time Complexity: O(n)
Description: 
*******************************************************************************/
void AVLDestroy(avl_t *avl);

/*******************************************************************************
AVLInsert
Time Complexity: O(log n)
Description: 
NOTE: Can't insert value that already exists.
*******************************************************************************/
int AVLInsert(avl_t *avl, void *new_data);

/*******************************************************************************
AVLDelete
Time Complexity: O(log n)
Description: 
*******************************************************************************/
void AVLRemove(avl_t *avl, const void *to_remove);

/*******************************************************************************
AVLFind
Time Complexity: O(log n)
Description: 
Returns reference to the data if found, else returns NULL
*******************************************************************************/
void *AVLFind(const avl_t *avl, const void *to_search);

/*******************************************************************************
AVLCount
Time Complexity: O(n)
Description: Return the number of elements in the given avl.
*******************************************************************************/
size_t AVLCount(const avl_t *avl);

/*******************************************************************************
AVLIsEmpty
Time Complexity: O(1)
Description:
Return TRUE (1) if it's empty, else return FALSE (0).
*******************************************************************************/
int AVLIsEmpty(const avl_t *avl);

/*******************************************************************************
AVLForEach
Time Complexity: O(n)
Description: Does action on all the nodes of the given avl. Returns:
SUCCESS : 0 (success for all)
FAILURE : non zero (the return failure value of the action func, returns after first failure)
*******************************************************************************/
int AVLForEach(avl_t *avl, avl_action_func_t act_func, void *param, 
				int order_type);

/*******************************************************************************
AVLHeight
Time Complexity: O(1)
Description: Returns the height of the given avl
*******************************************************************************/
size_t AVLHeight(const avl_t *avl);


#endif /*__AVL_H__*/
