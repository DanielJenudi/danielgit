#include <stdio.h>

/*declaretion of function*/
void Hello_World ();
float Pow (float s_num, int power);
int Fliper (int s_num);
void Swap (int *ptr_1, int *ptr_2);


int  main()
{

int x = 4, y = 5; /*for Swap function check*/


Hello_World();


Pow( 10, 0 );


Fliper( -1234 );


Swap( &x, &y );
printf("after swap: %d , %d\n", x, y); /*check if swap*/


return 0;

}



void Hello_World()
{

	int arr[] = {0x22, 0x48, 0x65, 0x6c, 0x6c, 0x6f, /*array of hex*/
	0x20, 0x57, 0x6f, 0x72, 0x6c, 0x64, 0x21, 0x22}; 

	int size = sizeof (arr) / sizeof (int);  /*size of arr*/

	int i = 0;/*for the loop*/


	for( i = 0; i <= size; i++ )
	{

		printf("%c",arr[i]);
	}
	
	printf("\n"); /*new line*/

}



float Pow (float s_num, int power)
{
	
	
	float result = 1.0;
	 
	int i = 0;/*for the loop*/
	
	if( power < 0 )
	{

		power *= (-1);/*change the power to positiv*/
		s_num = 1/s_num;/*change the variable to fraction*/
	}
		
	
	for( i = 0; i < power; i++ )
	{
	
		result *= s_num;
	
	}
	
	
	printf("pow result %f\n", result); /*print result*/

	return result;
	
}



int Fliper (int s_num)
{

	int result = 0;
	
	while( s_num != 0 ) /*flip the number*/
	{
			
		result *= 10; 
		result += s_num % 10;	
		s_num /= 10;		
		
	}
	
	
	printf("fliper result %d\n", result); /*print result*/
	
	return result;
	
	
}


void Swap (int *ptr_1, int *ptr_2)
{

	int swap_point; /*waiting place for int*/
	
	printf("befor swap: %d , %d\n", *ptr_1, *ptr_2); /*check befor*/
	
	
	swap_point = *ptr_1;
	*ptr_1 = *ptr_2;
	*ptr_2 = swap_point;
	
	
	/*after checking in main*/
	
}








	
