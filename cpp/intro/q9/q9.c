#include <iostream>

void foo(int, int i = 3, float = 4);

int main()
{
    foo(3);
    foo(6, 5);
    foo(4, 7, 8.7);

    // hello

    /*
    hello
    */

    return 0;
}

void foo(int x, int y, float z)
{
    std ::cout << "\nx: " << x << "\ny: " << y << "\nz: " << z << std ::endl;
}