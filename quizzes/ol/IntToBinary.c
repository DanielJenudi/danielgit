#include <stdio.h> /* printf */

#define NUM_OF_BITS_IN_INT (32)

char *IntToBinary(char *result, int num);

int main()
{
    char str[NUM_OF_BITS_IN_INT + 1] = {0};
    int num = 143982;

    IntToBinary(str, num);

    printf("%s\n", str);

    return 0;
}

char *IntToBinary(char result[], int num)
{
    size_t i = 0;

    for (i = 0; i < NUM_OF_BITS_IN_INT; ++i)
    {

        result[i] = (char)((num & 1) + 48);
        /*printf("%d\n", (num & 1));*/
        num >>= 1;
    }

    return result;
}
