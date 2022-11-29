#include <stdio.h> /* printf */

// g++ -std=c++98 -fPIC -c -o libfoo.o libfoo.cpp
// gcc -shared -o libfoo.so libfoo.o

void foo()
{
    printf("nothing\n");
}

void Foo(int i)
{
    printf("%d\n", i);
}

void Foo(char c)
{
    printf("%c\n", c);
}

void Foo(char *str)
{
    printf("%s\n", str);
}

void Foo(float f)
{
    printf("%f\n", f);
}

void Foo(unsigned char c)
{
    printf("unsigned char: %c\n", c);
}
