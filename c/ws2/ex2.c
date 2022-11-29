#include <stdio.h>
#include <stdlib.h>


/*declaretion of function*/
void Swap (int *ptr_1, int *ptr_2);/*swap two integers*/
int *CopyArray (int *arr, int *n_arr, int size);/*copy array to new array*/
void SwapSizeT (size_t *ptr_1, size_t *ptr_2);/*swap tow size_t*/
void SwapPointer (size_t **ptr_1, size_t **ptr_2);/*swap two pointers*/
void PrintAddresses ();/*question 3, print address*/
void TestSwap();/*test for Swap*/
void TestCopyArray();/*test for CopyArray*/
void TestSwapSizeT ();/*test for SwapSizeT*/
void TestSwapPointer ();/*test for SwapPointer*/
void TestPointerSwapSizeT();/*question 4 point 3, test for swap pointers with SwapSizeT*/


int  main()
{	
	TestSwap(); /*Swap function*/
	
	TestCopyArray();/*CopyArray function*/

	TestSwapSizeT(); /*SwapSizeT function*/
	
	TestSwapPointer();/*SwapPointer function*/
	
	TestPointerSwapSizeT();/*Exrecise 4 point 3 function*/
	
	PrintAddresses();/*question 3*/

	return 0;
}

void Swap (int *ptr_1, int *ptr_2)
{
	int swap_point = 0; /*waiting place for int*/
	
	swap_point = *ptr_1;
	*ptr_1 = *ptr_2;
	*ptr_2 = swap_point;
}

void TestSwap()
{
	int x = 2, y = 3;
	
	printf("befor swap: %d , %d\n", x, y); /*check befor*/
	Swap(&x, &y);
	printf("after swap: %d , %d\n\n", x, y); /*check if swap*/
}

int *CopyArray (int *arr, int *n_arr, int size) 
{
	int i = 0; /*for the loops*/

	for( i = 0; i < size; ++i )
	{
		n_arr[i] = arr[i];
	}
	
	return n_arr;

}

void TestCopyArray()
{	
	int arr[] = { 1, 2, 3, 4 }; 
	int size_arr = sizeof (arr) / sizeof (int); /*the size of arr*/
	int cp_arr[4];
	int i = 0; 
	
	CopyArray(arr, cp_arr, size_arr);
	
	/*print both array*/
	printf("check if the array copy\narr:	arr_cp:\n");

	for( i = 0; i < size_arr; ++i )
	{
		printf("%d	%d\n", arr[i], cp_arr[i]);
	}
	
	printf("\n");
}

void SwapSizeT (size_t *ptr_1, size_t *ptr_2)
{
	size_t swap_point = 0; /*waiting place for size_t*/

	swap_point = *ptr_1;
	*ptr_1 = *ptr_2;
	*ptr_2 = swap_point;
}

void TestSwapSizeT ()
{
	size_t x_t = 4, y_t = 5;
	
	printf("befor swap size_t: %lu , %lu\n", x_t, y_t); /*check befor*/
	SwapSizeT(&x_t, &y_t);
	printf("after swap size_t: %lu , %lu\n\n", x_t, y_t); /*check after*/
}


void SwapPointer (size_t **ptr_1, size_t **ptr_2)
{
	size_t *swap_point = NULL; /*waiting place for pointer size_t*/

	swap_point = *ptr_1;
	*ptr_1 = *ptr_2;
	*ptr_2 = swap_point;	
}

void TestSwapPointer ()
{
	size_t x_t = 4, y_t = 5;
	size_t *ptr_1 = &x_t, *ptr_2 = &y_t;

	printf("befor swap pointer, pointer status: \nptr_x_t: %p , ptr_y_t: %p\n",
	      (void  *)ptr_1, (void  *)ptr_2); /*check befor*/
	SwapPointer(&ptr_1, &ptr_2);
	printf("after swap pointer, pointer status: \nptr_x_t: %p , ptr_y_t: %p\n\n",
	      (void  *)ptr_1, (void  *)ptr_2); /*check after*/
}

void TestPointerSwapSizeT ()
{
	size_t x_t = 4, y_t = 5;
	size_t *ptr_1 = &x_t, *ptr_2 = &y_t;
	
	printf("befor swap pointe with swapsize_t: %p , %p\n", 
	      (void  *)ptr_1, (void  *)ptr_2); /*check befor*/
	SwapSizeT((size_t *)&ptr_1, (size_t *)&ptr_2 );
	printf("befor swap pointe with swapsize_t: %p , %p\n\n",
	      (void  *)ptr_1, (void  *)ptr_2); /*check after*/
}

/*question 3*/
void PrintAddresses ()
{
  
	static int s_i = 7;
        int i = 7;
        int *ptr = &i;
        int *ptr2 = (int *)malloc(sizeof(int));
    
        printf("question 3:\n");
    
        if(ptr)
        {
            int **ptr3 = &ptr;
            printf("ptr3 = %p\n", (void *)ptr3);
        }
    
        printf("s_i =%p\ni = %p\nptr = %p\nptr2 = %p\n",(void *)&s_i,
              (void *)&i,(void *)&ptr, (void *)ptr2);
    
        free(ptr2);
    
}


