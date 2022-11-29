/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Name: Daniel Jenudi
Reviewer: 
Date: 01/05/2022
File: Calculate
Description: Source file
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/

#include <stdlib.h>/* malloc, free */
#include <string.h>/* strtod */
#include <assert.h>/* assert */


#include "calc.h"/* Calculate */
#include "stack.h"/* StackCreate, StackDestroy, StackPush, 
					 StackPop, StackPeek, StackIsEmpty */

#define STACKSIZE 100
#define ASCII 256

#define RELEVENT_OPERATORS (NUM_OF_OPERATORS - 2)
#define BINARY_LUT 2
#define END_OF_EXPRETION NUM_OF_INPUTS
#define LOW_PRIORITY 1
#define HIGH_PRIORITY 2
#define PARNTHESE 3
#define NUM_OF_STATUS 4

enum input_types
{
    OPERATOR = 0,
    NUMBER,
    OPEN_PAR,
    CLOSE_PAR,
    END,
    INVALID,
    NUM_OF_INPUTS
};

enum states
{
	START= 0,
    WAIT_FOR_OPERAND,
    WAIT_FOR_OPERATOR,
    OPEN_PAR_STATE,
    NUM_OF_STATES
};

enum operators_actions
{
	PLUS,
	MINOS,
	MULTIPLIER,
	DIVISION,
	OPEN_PAR_OPERATION,
    CLOSE_PAR_OPERATION,
	NUM_OF_OPERATORS
};

typedef void (*boolean_lut_t)();
typedef int (*close_par_t)(stack_t *operator_stack);
typedef int (*operators_action_lut_t)(double *result, double operand);
typedef int (*transition_t)(stack_t *operator_stack, stack_t *operand_stack,
							char **expression, int *state);

static int Minos(double *result, double operand);
static int Plus(double *result, double operand);
static int Multipluer(double *result, double operand);
static int Division(double *result, double operand);

static void InitLUTs();
static void DoNothing();
static void InitInputLut();
static void InitOparationLut();
static size_t OperatorStackSize(const char *exp);
static size_t OperandStackSize(const char *exp, size_t operator_stack_size);

static int WaitForOperator(stack_t *operator_stack, stack_t *operand_stack,
				    char **expression, int *state);
static int WaitForOperand(stack_t *operator_stack, stack_t *operand_stack,
				    char **expression, int *state);
static int CalcAndRet(stack_t *operator_stack, stack_t *operand_stack,
				    char **expression, int *state);
static int Error(stack_t *operator_stack, stack_t *operand_stack,
				    char **expression, int *state);
static int Ret0(stack_t *operator_stack, stack_t *operand_stack,
				    char **expression, int *state);
static int Close_Par(stack_t *operator_stack, stack_t *operand_stack,
				    char **expression, int *state);
static int Open_Par(stack_t *operator_stack, stack_t *operand_stack,
				    char **expression, int *state);
static int StartOperator(stack_t *operator_stack, stack_t *operand_stack,
					char **expression, int *state);

static int CloseParFail (stack_t *operator_stack);
static int CloseParSuccess (stack_t *operator_stack);

static int Parse(char c);
static int CalcTowOperands(stack_t *operator_stack, stack_t *operand_stack);

/* ~~~~~ LUTS ~~~~~ */

static char g_operation_lut[ASCII] = {0};
static char input_lut[ASCII] = {0};

static const close_par_t g_close_par_lut[BINARY_LUT] = 
	{&CloseParSuccess, &CloseParFail};

static const int g_division_lut[BINARY_LUT] = 
	{MATH_ERROR, SUCCESS};
	
static const boolean_lut_t g_init_lut[BINARY_LUT] =
	{&InitLUTs, &DoNothing};

static const int g_priority_lut[NUM_OF_OPERATORS] = 
	{LOW_PRIORITY, LOW_PRIORITY, HIGH_PRIORITY, 
										   HIGH_PRIORITY, PARNTHESE, PARNTHESE};

static const operators_action_lut_t g_operators_action_lut[NUM_OF_OPERATORS] = 
	{&Plus, &Minos, &Multipluer, &Division};

static const transition_t g_state_input[NUM_OF_STATES][NUM_OF_INPUTS] = {
	{&StartOperator, &WaitForOperand, &Open_Par, &Error, &Ret0, &Error},
	{&Error, &WaitForOperand, &Open_Par, &Error, &Error, &Error},
	{&WaitForOperator, &Error, &Error, &Close_Par, &CalcAndRet, &Error},
	{&StartOperator, &WaitForOperand, &Open_Par, &Error, &Error, &Error}
	};

static const transition_t g_operator_start[RELEVENT_OPERATORS] = 
	{&WaitForOperand, &WaitForOperand, &Error, &Error};
	
static const int g_return_status_lut[NUM_OF_STATUS][NUM_OF_STATUS] = {
	{SUCCESS, SYNTAX_ERROR, MATH_ERROR, ALLOC_ERROR},
	{SYNTAX_ERROR, SYNTAX_ERROR, SYNTAX_ERROR, SYNTAX_ERROR},
	{MATH_ERROR, SYNTAX_ERROR, MATH_ERROR, MATH_ERROR},
	{ALLOC_ERROR, ALLOC_ERROR, ALLOC_ERROR, ALLOC_ERROR}
	};
	
/* ~~~~~ main function ~~~~~ */

int Calculate(const char *expression , double *result)
{	
	stack_t *operands_stack = NULL;
	stack_t *operators_stack = NULL;
	size_t operands_stack_size = 0;
	size_t operators_stack_size = 0;
	int state = START;
	int input = 0;
	int return_status = SUCCESS;
	static int flag = 0;
	
	assert(NULL != expression);
	assert(NULL != result);	
	
	(*g_init_lut[flag])();
	flag = 1;
	
	operators_stack_size = OperatorStackSize(expression);
	operands_stack_size = OperandStackSize(expression, operators_stack_size);
	
	operators_stack = StackCreate(operators_stack_size, sizeof(char));
	if(NULL == operators_stack)
	{
		return ALLOC_ERROR;
	}
	
	operands_stack = StackCreate(operands_stack_size + 2, sizeof(double));
	if(NULL == operands_stack)
	{
		StackDestroy(operands_stack);
		operands_stack = NULL;
		return ALLOC_ERROR;
	}
	
	while((END_OF_EXPRETION != state) && (SUCCESS == return_status))
	{
		input = Parse(*expression);
		return_status = (*g_state_input[state][input])(
				operators_stack, operands_stack, (char **)&expression, &state);
	}
	
	*result = *(double *)StackPeek(operands_stack);
	
	StackDestroy(operators_stack);
	operators_stack = NULL;
	StackDestroy(operands_stack);
	operands_stack = NULL;

	return return_status;
}

static int Parse(char c)
{
	return input_lut[(int)c];
}

/* ~~~~~ stack size ~~~~~ */

static size_t OperatorStackSize(const char *exp)
{
	int arr[NUM_OF_INPUTS] = {0};
	char *runner = (char *)exp;
	
	assert(NULL != exp);
	
	runner = (char *)exp;
	
	while('\0' != *runner)
	{
		++arr[(int)input_lut[(int)*runner]];
		++runner;
	}

	return  arr[OPERATOR] + arr[OPEN_PAR];
}

static size_t OperandStackSize(const char *exp, size_t operator_stack_size)
{
	char *runner = (char *)exp;

	assert(NULL != exp);

	runner = (char *)exp;
	return  strlen(runner) - operator_stack_size;
}

/* ~~~~~ states ~~~~~ */

static int CalcTowOperands(stack_t *operator_stack, stack_t *operand_stack)
{
	double operand = 0;
	char excute_operator = '\0';
	
	assert(NULL != operator_stack);
	assert(NULL != operand_stack);
	
	operand = *(double *)StackPeek(operand_stack);
	StackPop(operand_stack);
	
	excute_operator = *(char *)StackPeek(operator_stack);
	StackPop(operator_stack);
	
	return g_operators_action_lut[(int)g_operation_lut[(int)excute_operator]](
		   (double *)StackPeek(operand_stack), operand);		
}

static int WaitForOperand(stack_t *operator_stack, stack_t *operand_stack,
				 		  char **expression, int *state)
{
	double num = 0;
	
	assert(NULL != operator_stack);
	assert(NULL != operand_stack);
	assert(NULL != expression);
	assert(NULL != state);
	
	(void)operator_stack;
	
	num = strtod(*expression, expression);
	StackPush(operand_stack, &num);
	*state = WAIT_FOR_OPERATOR;
	
	return SUCCESS;
}

static int WaitForOperator(stack_t *operator_stack, stack_t *operand_stack,
				           char **expression, int *state)
{
	char operator = '\0';
	int return_status = SUCCESS;
	
	assert(NULL != operator_stack);
	assert(NULL != operand_stack);
	assert(NULL != expression);
	assert(NULL != state);
	
	operator = **expression;
	
	(void)operand_stack;
	
	while((!StackIsEmpty(operator_stack))&&
    	  (return_status == SUCCESS) &&
    	  (*(char *)StackPeek(operator_stack) != '(') &&
		  (g_priority_lut[(int)g_operation_lut[(int)operator]]) <= 
		  (g_priority_lut[(int)g_operation_lut[
		  						     (int)*(char *)StackPeek(operator_stack)]]))
	{
		return_status = CalcTowOperands(operator_stack, operand_stack);
	}	
	
	StackPush(operator_stack, &operator);
	++*expression;
	*state = WAIT_FOR_OPERAND;
	
	return return_status;	
}

static int Open_Par(stack_t *operator_stack, stack_t *operand_stack,
				      char **expression, int *state)
{
	char operator = '\0';
	
	assert(NULL != operator_stack);
	assert(NULL != operand_stack);
	assert(NULL != expression);
	assert(NULL != state);
	
	(void)operand_stack;
	
	operator = **expression;
	StackPush(operator_stack, &operator);
	++*expression;
	*state = OPEN_PAR_STATE;
	
	return SUCCESS;	
}

static int Close_Par(stack_t *operator_stack, stack_t *operand_stack,
				      char **expression, int *state)
{
	int return_status = SUCCESS;
	int parse_status = SUCCESS;
	
	assert(NULL != operator_stack);
	assert(NULL != operand_stack);
	assert(NULL != expression);
	assert(NULL != state);
	
	while((!StackIsEmpty(operator_stack)) &&
    	  (return_status == SUCCESS) &&
		  ('(' != *(char *)StackPeek(operator_stack)))
	{
		return_status = CalcTowOperands(operator_stack, operand_stack);
	}
	
	parse_status = 
		(*g_close_par_lut[StackIsEmpty(operator_stack)])(operator_stack);
	++*expression;
	*state = WAIT_FOR_OPERATOR;
	
	return g_return_status_lut[return_status][parse_status];
}

static int CalcAndRet(stack_t *operator_stack, stack_t *operand_stack,
				      char **expression, int *state)
{	
	int return_status = SUCCESS;
	int parse_status = SUCCESS;
	(void)expression;

	assert(NULL != operator_stack);
	assert(NULL != operand_stack);
	assert(NULL != expression);
	assert(NULL != state);

	while((!StackIsEmpty(operator_stack) && return_status == SUCCESS) &&
	      (*(char *)StackPeek(operator_stack) != '('))
	{
		return_status = CalcTowOperands(operator_stack, operand_stack);
	}
	
	parse_status = 
		!(*g_close_par_lut[StackIsEmpty(operator_stack)])(operator_stack);
	
	*state = END_OF_EXPRETION;
	
	return g_return_status_lut[return_status][parse_status];	
}

static int Error(stack_t *operator_stack, stack_t *operand_stack,
				 char **expression, int *state)
{	
	double num = 0;
	
	assert(NULL != operator_stack);
	assert(NULL != operand_stack);
	assert(NULL != expression);
	assert(NULL != state);
	
	(void)operator_stack;
	(void)expression;
	(void)state;
	
	StackPush(operand_stack, &num);
	
	return SYNTAX_ERROR;	
}

static int Ret0(stack_t *operator_stack, stack_t *operand_stack,
				char **expression, int *state)
{	
	double num = 0;
	
	assert(NULL != operator_stack);
	assert(NULL != operand_stack);
	assert(NULL != expression);
	assert(NULL != state);
	
	(void)operator_stack;
	(void)expression;
	
	StackPush(operand_stack, &num);
	*state = END_OF_EXPRETION;
	
	return SUCCESS;	
}

static int StartOperator(stack_t *operator_stack, stack_t *operand_stack,
					   	 char **expression, int *state)
{	
	assert(NULL != operator_stack);
	assert(NULL != operand_stack);
	assert(NULL != expression);
	assert(NULL != state);
	
	return (*g_operator_start[(int)g_operation_lut[(int)**expression]])
		   (operator_stack, operand_stack, expression, state);
}

/* ~~~~~ parse syntax error ~~~~~ */

static int CloseParSuccess (stack_t *operator_stack)
{
	assert(NULL != operator_stack);

	StackPop(operator_stack);
	
	return SUCCESS;
}

static int CloseParFail (stack_t *operator_stack)
{
	assert(NULL != operator_stack);

	(void)operator_stack;
	
	return SYNTAX_ERROR;
}

/* ~~~~~ init luts ~~~~~ */

static void InitLUTs()
{
	InitOparationLut();
	InitInputLut();
}

static void DoNothing(){}

static void InitInputLut()
{
	int i = 0;
	
	for(i = 0; i < ASCII; ++i)
	{
		input_lut[i] = INVALID;
	}
	
	input_lut[(int)'0'] = NUMBER;
	input_lut[(int)'1'] = NUMBER;
	input_lut[(int)'2'] = NUMBER;
	input_lut[(int)'3'] = NUMBER;
	input_lut[(int)'4'] = NUMBER;
	input_lut[(int)'5'] = NUMBER;
	input_lut[(int)'6'] = NUMBER;
	input_lut[(int)'7'] = NUMBER;
	input_lut[(int)'8'] = NUMBER;
	input_lut[(int)'9'] = NUMBER;
	
	input_lut[(int)')'] = CLOSE_PAR;
	input_lut[(int)'('] = OPEN_PAR;
	input_lut[(int)'*'] = OPERATOR;
	input_lut[(int)'/'] = OPERATOR;
	input_lut[(int)'+'] = OPERATOR;
	input_lut[(int)'-'] = OPERATOR;
	
	input_lut[(int)'\0'] = END;
}

static void InitOparationLut()
{
	int i = 0;
	
	for(i = 0; i < ASCII; ++i)
	{
		g_operation_lut[i] = INVALID;
	}
	
	g_operation_lut[(int)')'] = CLOSE_PAR_OPERATION;
	g_operation_lut[(int)'('] = OPEN_PAR_OPERATION;
	g_operation_lut[(int)'*'] = MULTIPLIER;
	g_operation_lut[(int)'/'] = DIVISION;
	g_operation_lut[(int)'+'] = PLUS;
	g_operation_lut[(int)'-'] = MINOS;
}

/* ~~~~~ operations ~~~~~ */

static int Plus(double *result, double operand)
{
	assert(NULL != result);

	*result += operand;
	
	return SUCCESS;
}

static int Minos(double *result, double operand)
{
	assert(NULL != result);

	*result -= operand;
	
	return SUCCESS;
}

static int Multipluer(double *result, double operand)
{
	assert(NULL != result);
	
	*result *= operand;
	
	return SUCCESS;
}

static int Division(double *result, double operand)
{
	assert(NULL != result);

	*result /= operand;
	
	return g_division_lut[!!operand];
}


