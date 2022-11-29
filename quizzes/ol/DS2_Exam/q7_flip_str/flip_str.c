#include <string.h> /* strlen */
#include <stdio.h>  /* printf */
#include <assert.h> /* assert */

void Swap(char *x, char *y);
void FlipStr(char *str);
void RecFlip(char *start, char *end);

int main()
{
    char str[] = "hello world";

    FlipStr(str);

    printf("%s\n", str);

    return 0;
}

void FlipStr(char *str)
{
    char *start = NULL;
    char *end = NULL;

    assert(NULL != str);

    start = str;
    end = str + strlen(str) - 1;

    RecFlip(start, end);
}

void RecFlip(char *start, char *end)
{
    if (start >= end)
    {
        return;
    }

    Swap(start, end);
    RecFlip(start + 1, end - 1);
}

void Swap(char *x, char *y)
{
    char temp;

    temp = *x;
    *x = *y;
    *y = temp;
}