#include <stdio.h>/* printf */

int CheckBoth2_6(unsigned char c);
int CheckOr2_6(unsigned char c);
void Swap3_5(unsigned char *c);

void SwapInts(int *x, int *y);
void SwapPointers(int **x, int **y);
void SwapVoidPointers(void **x, void **y);

int main()
{
	unsigned char a = 34;
	unsigned char b = 2;
	unsigned char c = 16;	
	
	int x = 3;
	int y = 5;
	int *ptrx = &x;
	int *ptry = &y;
	
	/* Q1 */
	printf("CheckBoth2_6: %d\n", CheckBoth2_6(a));
	printf("CheckOr2_6: %d\n", CheckOr2_6(b));
	printf("befor Swap3_5: %d\n", (int)c);
	Swap3_5(&c);
	printf("after Swap3_5: %d\n", (int)c);

	/* Q2 */
	SwapInts(ptrx, ptry);
	printf("x: %d y: %d\n", x, y);
	
	/* Q3 */
	x = 3;
	y = 5;
	SwapPointers(&ptrx, &ptry);
	printf("x: %d y: %d\n", *ptrx, *ptry);
	
	/* Q4 */
	ptrx = &x;
	ptry = &y;
	SwapVoidPointers((void **)&ptrx, (void **)&ptry);
	printf("x: %d y: %d\n", *ptrx, *ptry);

	return 0;
}

/* Q1 */

int CheckBoth2_6(unsigned char c)
{
	return ((c >> 1) & 1) & ((c >> 5) & 1);
}

int CheckOr2_6(unsigned char c)
{
	return !!(((c >> 1) & 1) + ((c >> 5) & 1));
}

void Swap3_5(unsigned char *c)
{
	int c3 = (*c >> 2) & 1;
	int c5 = (*c >> 4) & 1;
	int combine = c3 ^ c5;
	
	combine = (combine << 2) | (combine << 4);
	*c ^= combine;
}

/* Q2 */

void SwapInts(int *x, int *y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}

/* Q3 */

void SwapPointers(int **x, int **y)
{
	int *temp = *x;
	*x = *y;
	*y = temp;
}

/* Q4 */

void SwapVoidPointers(void **x, void **y)
{
	void *temp = *x;
	*x = *y;
	*y = temp;
}



