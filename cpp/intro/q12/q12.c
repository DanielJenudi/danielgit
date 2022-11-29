#include <stdio.h> /* printf */

void Foo();
void Foo(int i);
void Foo(char c);
void Foo(char *str);
void Foo(float f);
void Foo(unsigned char c);

int main()
{
    char str[] = {"hello"};
    unsigned char c = 41;
    float f = 3.3;

    Foo();
    Foo(69);
    Foo('c');
    Foo(NULL);
    Foo(f);
    Foo(c);

    return 0;
}

void Foo()
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
