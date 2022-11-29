/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Name: Daniel Jenudi
Reviewer: Amir L
Date: 09/05/2022
File: Recursion
Description: Header file
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/*******************************************************************************
                      			  Recursion
*******************************************************************************/


#ifndef __RECURSION_H__
#define __RECURSION_H__


#include <stddef.h>

typedef struct singly_linked_list node_t;
typedef struct stack stack_t;

/* Fibonacci */
int RecFibonacciIterative(int element_index);
int RecFibonacci(int element_index);

/* String */
size_t RecStrLen(const char *str);
int RecStrCmp(const char *str1, const char *str2);
char *RecStrCpy(char *dest, const char *src);
char *RecStrCat(char *dest, const char *src);
char *RecStrStr(const char *haystack, const char *needle);

/* SLL */
node_t *SLLCreate(int first_data);
void SLLDestroy(node_t *node);
node_t *SLLInsertBefore(node_t *node, int data);
node_t *SLLNext(node_t *node);
int SLLGetValue(node_t *node);
node_t *RecFlipList(node_t *head);
/*implement simple list without #including "sll.h" */


/* STACK */
/*implement simple stack without #including "stack.h" */
stack_t *StackCreate(size_t capacity);
void StackDestroy(stack_t *stack);
void StackPop(stack_t *stack);
int StackPeek(const stack_t *stack);
void StackPush(stack_t *stack, int data);
int StackIsEmpty(stack_t *stack);
stack_t *RecSortStack(stack_t *stack);

#endif   /*__RECURSION_H__*/


