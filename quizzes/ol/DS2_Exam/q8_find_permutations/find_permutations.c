#include <string.h> /* strlen */
#include <stdio.h>  /* printf */
#include <assert.h> /* assert */

void PrintPermutations(char *str);
void ReqFunc(char *str, size_t start, size_t end);
void Swap(char *x, char *y);

int main()
{
    char str[] = "ABCD";

    PrintPermutations(str);

    return 0;
}

void PrintPermutations(char *str)
{
    assert(NULL != str);
    ReqFunc(str, 0, strlen(str) - 1);
}

void ReqFunc(char *str, size_t start, size_t end)
{
    size_t i = 0;

    if (start == end)
    {
        printf("%s\n", str);
    }
    else
    {
        for (i = start; i <= end; ++i)
        {
            Swap(&str[i], &str[start]);
            ReqFunc(str, start + 1, end);
            Swap(&str[i], &str[start]);
        }
    }
}

void Swap(char *x, char *y)
{
    char temp;

    temp = *x;
    *x = *y;
    *y = temp;
}