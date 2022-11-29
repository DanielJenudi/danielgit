/*******************************************************************************
		   _\_   				   _\_					       _\_      
		\\/  o\					\\/  o\						\\/  o\		
		//\___=					//\___=						//\___=


					oooooooooooo  .oooooo..o       .o.       
          O  		`888'     `8 d8P'    `Y8      .888.      o   _/,_
   _\_   o			 888         Y88bo.          .8"888.      . /o...\__//
\\/  o\ .			 888oooo8     `"Y8888o.     .8' `888.       \_'__/``\`
//\___=				 888    "         `"Y88b   .88ooo8888.   	  \`
   ''				 888         oo     .d8P  .8'     `888.  
					o888o        8""88888P'  o88o     o8888o 

		 O
		o   _/,_			 		 _/,_					   _\_   o   
		 . /o...\__//				/o...\__//				\\/  o\ .		
		   \_'__/``\`				\_'__/``\`				//\___=
		     \`						  \`

********************************************************************************

		   _.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._
		 ,'_.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._`.
		( (                                                         ) )
		 ) )                                                       ( (
		( (              Author: Daniel Jenudi                      ) )
		 ) )             Date: 3/4/22                              ( (
		( (              Reviewed By: Chen Rudi						) )
		 ) ) 		     File: Fixed Size Allocators	           ( (
		( (			     Description: Header File                   ) )
		 ) )                                                       ( (
		( (_.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._) )
		 `._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._,'


********************************************************************************
DESCRIPTION: 
Fixed Size Allocators (aka FSA) memory are used to solve at least two types of 
memory related problems. First, global heap allocations/deallocations can be 
slow and nondeterministic. You never know how long the memory manager is going 
to take. Secondly, to eliminate the possibility of a memory allocation fault 
caused by a fragmented heap – a valid concern, especially on mission-critical 
type systems.

Attributes and policy:
- request size to hold, by user needs.
- alloc and free space by user block size rerest
- all blocks are alignd
- free same place twice is undefined behavior
- FSA is not responsible to free the allocation memory in the end of the process

--------------------------------------------------------------------------------

Operations on FSA:
- request memory pool size for user needs input
- initialize memory pool to be managed by FSA
- alloc block of space
- free block of space back to the pool
- get free space in the memory pool

*******************************************************************************/

#ifndef __FSA_H__
#define __FSA_H__

#include <stddef.h> /* size_t */

/*******************************************************************************
                                 Typedefs
*******************************************************************************/

typedef struct fsa fsa_t;

/*******************************************************************************
                                 Operations
*******************************************************************************/

/* Note: In case of wrong reference, undefined behavior occurs.
for example sending the wrong pool, sending block that already was free */


/*******************************************************************************
FSAReqPoolSize
Description: demands memory size for manage user request
Parameters: 
	- number of blocks
	- size of each block
Return value:
	- memory size for manage user request
Complexity: O(1) time
*******************************************************************************/
size_t FSAReqPoolSize(size_t nblocks, size_t block_size);

/*******************************************************************************
FSAInit
Description: initialize memory pool to be managed by FSA
Parameters: 
	- memory pool
	- number of blocks
	- size of each block
Return value:
	- FSA
Complexity: O(n) time
Notes: undefined behavior for Parameters that not connferm with FSAReqPoolSize.
	   all blocks are alignd.
*******************************************************************************/
fsa_t *FSAInit(void *mem_pool, size_t nblocks, size_t block_size);

/*******************************************************************************
FSACountFreeBlocks
Description: return the number of free blocks in a FSA
Parameters: 
	- FSA
Return value:
	- the number of free blocks in a FSA
Complexity: O(n) time 
*******************************************************************************/
size_t FSACountFreeBlocks(const fsa_t *pool);

/*******************************************************************************
FSAAlloc
Description: alloc block of memory from FSA for user use
Parameters: 
	- FSA
Return value:
	- pointer to new free space, if fail return NULL
Complexity: O(1) time
Notes: fail in case of max capacity 
*******************************************************************************/
void *FSAAlloc(fsa_t *pool);

/*******************************************************************************
FSAFree
Description: free block of memory back to FSA
Parameters: 
	- FSA
Complexity: O(1) time
Notes: free same block twice is undefined behavior
*******************************************************************************/
void FSAFree(fsa_t *pool, void *block); 

#endif /*__FSA_H__*/


