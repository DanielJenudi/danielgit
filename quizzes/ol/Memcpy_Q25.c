#include <stdio.h>/* print_f */

void *Memcpy(void *dest, void *src, size_t n);


int main()
{
	size_t i = 0;
	size_t n = 11;
	char dest[100];
	char src[] = "hello my name is daniel";
	 
	Memcpy(dest, src, n);
	
	for(i = 0; i < n; ++i)
	{
		printf("%c", dest[i]);
	}

	printf("\n");

	return 0;
}


void *Memcpy(void *dest, void *src, size_t n)
{
	void *dest_r = dest;
	void *src_r = src;

	while(sizeof(size_t) <= n)
	{
		*(size_t *)dest_r = *(size_t *)src_r;
		src_r = (size_t *)src_r + 1;
		dest_r = (size_t *)dest_r + 1;
		n -= sizeof(size_t);
	}

	while(0 < n)
	{
		*(char *)dest_r = *(char *)src_r;
		src_r = (char *)src_r + 1;
		dest_r = (char *)dest_r + 1;
		n -= sizeof(char);
	}
	
	return dest;
}








