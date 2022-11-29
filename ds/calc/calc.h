/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Name: Daniel Jenudi
Reviewer: 
Date: 01/05/2022
File: Calculate
Description: Header file
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/*******************************************************************************
                      			  Calculate
********************************************************************************

Attributes and policy:
-   get string and return the result
-   in case of syntax error return 1
-   in case of math error return 2
-	in case of alloc error return 3
-	in case of success return 0
-------------------------------------------------------------------------------

Operations on DS:
-	Calculates the result of a given string

*******************************************************************************/

#ifndef __CALC_H__
#define __CALC_H__

/*******************************************************************************
                      			Status Enum 
*******************************************************************************/

enum Status
{
    SUCCESS,
    SYNTAX_ERROR,
    MATH_ERROR,
    ALLOC_ERROR
};


/*******************************************************************************
Calculate
Description: Calculates the result of a given string
Parameters: 
	- pointer to double that contain the result
	- strinf expression
Return value:
	-   in case of syntax error return 1
	-   in case of math error return 2
	-	in case of alloc error return 3
	-	in case of success return 0
Complexity: O(n) time
Notes: in case of failure the result is un define. 
	   in case of empty string return 0.
*******************************************************************************/
int Calculate(const char *expression , double *result);

#endif   /*__CALC_H__*/

