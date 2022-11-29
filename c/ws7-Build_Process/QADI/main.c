#include "g.h"
#include <stdio.h>

int main()
{
	g_s = 3;
	printf("%d\n", g_s);
	foo();
	printf("%d\n", g_s);
	
	return 0;
}
