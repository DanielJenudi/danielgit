/* #include <iostream> */
#include <stdio.h>

struct A
{
};
struct B
{
    int x;
    int y;
};

int main()
{
    struct A a;
    struct B b;

    printf("size of a: %lu\n", sizeof(a));
    printf("size of b: %lu\n", sizeof(b));

    /*    std::cout << "size of a : " << sizeof(a) << std::endl;
       std::cout << "size of b : " << sizeof(b) << std::endl; */

    return 0;
}