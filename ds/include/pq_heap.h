/*******************************************************************************
░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░ 						
██████╗░██████╗░██╗░██████╗░██████╗░██╗████████╗██╗░░░██╗░░░░░░░░░░░░░░░░░░░░░░░     
██╔══██╗██╔══██╗██║██╔═══██╗██╔══██╗██║╚══██╔══╝╚██╗░██╔╝░░░░░░░░░░░░░░░░░░░░░░░    
██████╔╝██████╔╝██║██║░░░██║██████╔╝██║░░░██║░░░░╚████╔╝░░░░░░░░░░░░░░░░░░░░░░░░     
██╔═══╝░██╔══██╗██║██║░░░██║██╔══██╗██║░░░██║░░░░░╚██╔╝░░░░░░░░░░░░░░░░░░░░░░░░░      
██║░░░░░██║░░██║██║╚██████╔╝██║░░██║██║░░░██║░░░░░░██║░░░░░░░░░░░░░░░░░░░░░░░░░░       
╚═╝░░░░░╚═╝░░╚═╝╚═╝░╚═════╝░╚═╝░░╚═╝╚═╝░░░╚═╝░░░░░░╚═╝░░░░░░░░░░░░░░░░░░░░░░░░░░        
░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░
░░░░░░░░░░░░░░░░░░░░░░░░░░░░░██████╗░██╗░░░██╗███████╗██╗░░░██╗███████╗░░░░░░░░░
░░░░░░░░░░░░░░░░░░░░░░░░░░░░██╔═══██╗██║░░░██║██╔════╝██║░░░██║██╔════╝░░░░░░░░░
░░░░░░░░░░░░░░░░░░░░░░░░░░░░██║░░░██║██║░░░██║█████╗░░██║░░░██║█████╗░░░░░░░░░░░
░░░░░░░░░░░░░░░░░░░░░░░░░░░░██║░░░██║██║░░░██║██╔══╝░░██║░░░██║██╔══╝░░░░░░░░░░░
░░░░░░░░░░░░░░░░░░░░░░░░░░░░╚██████╔╝╚██████╔╝███████╗╚██████╔╝███████╗░░░░░░░░░
░░░░░░░░░░░░░░░░░░░░░░░░░░░░░╚═════╝░░╚═════╝░╚══════╝░╚═════╝░╚══════╝░░░░░░░░░
░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░							 
********************************************************************************
Name: Daniel Jenudi
Reviewer: Rani 
Date: 27/03/2022
File: Data struct - Priorety queue
Description: header file
********************************************************************************

DESCRIPTION: A priority queue is an abstract data-type similar to a regular 
queue or stack data structure in which each element additionally has a 
"priority" associated with it. In a priority queue, an element with high 
priority is served before an element with low priority.
In a queue, the first-in-first-out rule is implemented whereas, in a priority 
queue, the values are removed on the basis of priority. The element with the 
highest priority is removed first.

Attributes and policy:
-	Every item has a priority associated with it.
-	An element with high priority is dequeued before an element with low 
	priority.
- 	If two elements have the same priority, they are served according to their 
	order in the queue.
-	Holding element by reference.
-	Size change acorrding to insert/delete. 

A node of a a priority queue will contains three parts −

🔹️   Data 	  − It will store the integer value.
🔹️   Next 	  − It will store the address of a next node
🔹️   Priority − It will store the priority which is an integer value. 

--------------------------------------------------------------------------------

Operations on PQ:
- create PQ
- destroy PQ
- add or remove node to PQ
- peek the head value of PQ
- get the number of nodes in PQ
- get if PQ is empty
- clear all nodes in PQ
- receive functions to search and erase value from PQ.


*******************************************************************************/

#ifndef __P_QUEUE_H__
#define __P_QUEUE_H__

#include <stddef.h>/* size_t */


/*******************************************************************************
                                 Typedefs
*******************************************************************************/

typedef struct pq pq_t;
typedef int(*pq_cmp_func_t)(const void *current_data, const void *new_data,
						    void *param);
typedef int(*pq_is_match_t)(const void *current_data, void *param);

/*******************************************************************************
                                 Operations
*******************************************************************************/
/*******************************************************************************
PQCreate
Description: creates a new PQ
Parameters: 
	- comper function
	- param
Return value:
	- in case of failure, will return null
Complexity: O(1) time
Notes: create EOL node ,that alwase be the last node, pointing to NULL and
store pointer to the PQ itself. 
*******************************************************************************/
pq_t *PQCreate(pq_cmp_func_t cmp_func, void *param);

/*******************************************************************************
PQDestroy
Description: destroy a PQ
Parameters: 
	- PQ
Complexity: O(n) time
*******************************************************************************/
void PQDestroy(pq_t *pq);
	
/*******************************************************************************
PQEnqueue
Description: insert new node with comper function policy.
Parameters: 
	- PQ
	- pointer to data
Return value:
	- iterator to the node with the new data
Complexity: O(1) time
Notes: undefined behavior for NULL data.
*******************************************************************************/
int PQEnqueue(pq_t *pq, void *data);

/*******************************************************************************
SLRemove
Description: Removes node from the head of PQ
Parameters: 
	- PQ
Return value:
	- the data that have been removed
Complexity: O(1) time
Notes: undefined behavior for EOL node.
*******************************************************************************/
void *PQDequeue(pq_t *pq);
	

/*******************************************************************************
PQIsEmpty
Description: return if PQ is empty
Parameters: 
	- PQ
Return value:
	- return 1 if PQ is empty, else return 0
Complexity: O(1) time
*******************************************************************************/
int PQIsEmpty(const pq_t *pq);

/*******************************************************************************
PQPeek
Description: get data from the head of the PQ
Parameters: 
	- PQ
Return value:
	- pointer to data
Complexity: O(1) time
*******************************************************************************/	
void *PQPeek(const pq_t *pq);

/*******************************************************************************
PQSize
Description: return the number of elements in a PQ
Parameters: 
	- PQ
Return value:
	- the number of elements in a PQ
Complexity: O(n) time 
*******************************************************************************/
size_t PQSize(const pq_t *pq);

/*******************************************************************************
PQClear
Description: clear all elements in PQ
	- PQ
Complexity: O(n) time
*******************************************************************************/	
void PQClear(pq_t *pq);

/*******************************************************************************
PQErase
Description: Search in PQ for data with match function. if the data found, 
			 return the data and erase it. 
	- PQ
	- match function
	- parametor to the function
Return value:
	- if succeed return the data and erase it from the PQ, else return the NULL.
Complexity: O(n) time
*******************************************************************************/
void *PQErase(pq_t *pq, void *param, pq_is_match_t is_match);


/********************************************************************************
                              ccc  c  c  ccc
                               $   $cc$  $==
                               $   $  $  $cc
=ccr=    ========================================================  _,r====c,
 )$F     =cc= ,z=""?b, `$c.     3$"    "$$" "$P" "3$" "$c,    "$" cP"     `$
 )$F      $$ zP      ?b $F?b,   3$      $$,/"     3$   $"?c,   $ z$
 )$F      $$<$F       $>$F  ?b, 3$      $$C       3$   $  "?c  $ $$     ,,,,
 )$F      $$ ?b      z$'$F   `?bJ$      $$`"c,    3$   $    "?c$ `$L      $$
,J$L,,,c" $$  "b,..,cP' $L     `?P      $$   ?b,  3$   $      "$  `?c,,.,,P"
`""""""' `""'   """"   `""      `'     """"  """ `""' """      "    `"""""

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@%%%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@%+-----=+#@@@@@@@@@@@@@@@                    @
@@@@@@@@@@@@@@@@@@@@@@@@%#**-:-::--:::-#@@@@@@@@@@@@@  Remember who you  @
@@@@@@@@@@@@@@@@@@@@@@@+-:::--:::.::--::=#@@@@@@@@@@@       Are...       @
@@@@@@@@@@@@@@@@@@@@@@*::.---==--=-.:---..-*%@@@@@@@@                    @
@@@@@@@@@@@@@@@@@@@@@%:::-+***=-==*+::--:....-*@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@#-=+****+=++++++-::::-:...:+@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@%***+==+***+++++++=::::-:... -@@@@@@@  @@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@*:--: .+***+++++++++:.::::... *@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@**+==+*****+++++++++=..::::....%@  @@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@#********+***+++++++=:..::::.. :@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@#***********+====+++-:::::::... =@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@**********+-:...::--::::.:::.... +@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@*****+++=-:.::......::::...... .. #@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@-:-:::::::::......::::.......   . .%@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@*::::::::::.....:::::........      .%@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@-::::::::.:::::::..........        .@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@=.::::::::::::.............         =@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@*::::::::::::............:::::.      .@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@%=.:::..::..............:------::.      %@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

*******************************************************************************/

#endif /*__P_QUEUE_H__*/
