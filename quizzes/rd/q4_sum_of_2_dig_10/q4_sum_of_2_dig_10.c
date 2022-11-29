#include <stdio.h>  /* printf */
#include <stddef.h> /* size_t */

#define ASCII_DIF (48)

enum ret_val
{
    FALSE = 0,
    TRUE
};

static int HaveSumOfStr10(char *str);

int main()
{
    char str[] = "26334";

    printf("result: %d\n", HaveSumOfStr10(str));

    return 0;
}

static int HaveSumOfStr10(char *str)
{
    size_t lut[10] = {0};
    size_t i = 0;

    while ('\0' != str[i])
    {
        ++lut[(size_t)str[i] - ASCII_DIF];
        ++i;
    }

    for (i = 1; i < 5; ++i)
    {
        if ((0 != lut[i]) && (0 != lut[10 - i]))
        {
            return TRUE;
        }
    }

    if (2 <= lut[5])
    {
        return TRUE;
    }

    return FALSE;
}