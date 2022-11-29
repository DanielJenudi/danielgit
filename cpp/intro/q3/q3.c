#include <stdio.h> /* ptintf */

int main()
{
    bool b1 = true;
    bool b2;
    /*int i = b1;
    i = 7;
    b2 = i;*/
    printf("b1: %ld\2\n", sizeof(b1));
    printf("b2: %d\2\n", b2);
}