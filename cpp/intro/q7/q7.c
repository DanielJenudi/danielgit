#include <stdio.h> /* printf */
#include <cstdlib> /* malloc, free */

int main()
{
    /* a */
    float *f = new float(12.6);

    printf("1: %f\n", *f);

    delete f;

    f = new float[15];

    for (size_t i = 0; i < 15; ++i)
    {
        f[i] = (float)i / 2;
    }

    for (size_t i = 0; i < 15; ++i)
    {
        printf("2: %f\n", f[i]);
    }

    delete[] f;

    /* e */
    int *ptr = (int *)malloc(10 * sizeof(int));

    delete ptr;

    int *ptr2 = new int[10];
    free(ptr);

    return 0;
}