#include <stdio.h>

int main()
{
    const int i = 3;
    int *ip = (int *)&i;

    int arr[i];

    *ip = 5;

    printf("i: %d ip: %d\n", i, *ip);

    printf("i: %lu ip: %lu\n", &i, ip);

    return 0;
}