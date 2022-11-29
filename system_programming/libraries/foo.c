#include <stdio.h>

const int global_const_var = 10;
int global_var = 20;

void foo(void)
{
	static const int static_local_const_var = 3;
	static int static_local_var = 4;
	char *str_literal = "Im A Literal String";

	puts("Hello, I am a shared library");

	printf("Im A Non-Const Global Variable - %d. ", global_var);
	printf("My address is: %p\n", (void*)&global_var);

	printf("Im A Const Global Variable - %d. ", global_const_var);
	printf("My address is: %p\n", (void*)&global_const_var);

	printf("Im A Const Static Local Variable - %d. ", static_local_const_var);
	printf("My address is: %p\n", (void*)&static_local_const_var);

	printf("Im A Non-Const Static Local Variable - %d. ", static_local_var);
	printf("My address is: %p\n", (void*)&static_local_var);
	
	printf("%s\n", str_literal);
	printf("My address is: %p\n", *(char**)&str_literal);
}

