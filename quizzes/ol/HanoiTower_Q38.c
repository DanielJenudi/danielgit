#include <stdio.h> /* printf */


void HanoiTower(int n, char from, char to, char aux);


int main()
{
	HanoiTower(3, 'A', 'B', 'C');
	
	return 0;
}


void HanoiTower(int n, char from, char to, char aux)
{
	if(1 == n)
	{
		printf("move %d from %c to %c\n", n ,from, to);
	}
	else
	{
		HanoiTower(n-1, from, aux, to);
		printf("move %d from %c to %c\n", n ,from, to);
		HanoiTower(n-1, aux, to, from);
	}
}
