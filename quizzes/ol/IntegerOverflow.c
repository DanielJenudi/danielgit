#include <stdio.h>  /* printf */
#include <string.h> /* strlen */

#define ASCII_DIF (48)

void AddLongNumbers(const char *num1, const char *num2, char *output);
void Revers(char *str);

int main()
{
    char num1[] = "99990952757379";
    char num2[] = "99120370175";
    char output[100] = {0};

    AddLongNumbers(num1, num2, output);

    printf("%s\n", output);

    return 0;
}

void AddLongNumbers(const char *num1, const char *num2, char *output)
{
    long rest = 0;
    long temp_res = 0;

    char *output_runner = output;
    const char *runner1 = num1 + (strlen(num1) - 1);
    const char *runner2 = num2 + (strlen(num2) - 1);
    const char *longer = NULL;

    while ((runner1 >= num1) && (runner2 >= num2))
    {
        temp_res = (*runner1 - ASCII_DIF) + (*runner2 - ASCII_DIF) + rest;
        rest = temp_res / 10;
        *output_runner = (temp_res % 10) + ASCII_DIF;

        ++output_runner;
        --runner1;
        --runner2;
    }

    if (runner1 >= num1)
    {
        longer = runner1;
    }
    else
    {
        longer = runner2;
    }

    while ('\0' != *longer)
    {
        temp_res = (*longer - ASCII_DIF) + rest;
        rest = temp_res / 10;
        *output_runner = (temp_res % 10) + ASCII_DIF;

        ++output_runner;
        --longer;
    }

    while (0 != rest)
    {
        *output_runner = (rest % 10) + ASCII_DIF;
        rest /= 10;
        ++output_runner;
    }

    Revers(output);
}

void Revers(char *str)
{
    char *end = str + (strlen(str) - 1);
    char *start = str;
    char temp = '\0';

    while (end > start)
    {
        temp = *end;
        *end = *start;
        *start = temp;

        --end;
        ++start;
    }
}