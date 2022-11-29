#include <stdio.h>
#include <assert.h>

enum
{
    SUCCESS = 0,
    FAIL
};

void Swap(char *x, char *y);
int SortCharsInFile(const char *file_name, char *result);

int main()
{
    char result[100] = {0};

    SortCharsInFile("txt.txt", result);
    printf("%s\n", result);

    return 0;
}

int SortCharsInFile(const char *file_name, char *result)
{
    FILE *file = NULL;
    char *runner = NULL;
    size_t len = 0, i = 0, j = 0;
    char c = '\0';

    assert(NULL != file_name);
    assert(NULL != result);

    runner = result;

    file = fopen(file_name, "r");
    if (NULL == file)
    {
        return FAIL;
    }

    c = fgetc(file);
    while (c != EOF)
    {
        ++len;
        *runner = c;
        ++runner;
        c = fgetc(file);
    }

    fclose(file);

    for (i = 0; i < (len - 1); ++i)
    {
        runner = result;
        for (j = 0; j < (len - 1); ++j)
        {
            if (*runner > *(runner + 1))
            {
                Swap(runner, runner + 1);
            }
            ++runner;
        }
    }

    return SUCCESS;
}

void Swap(char *x, char *y)
{
    char temp;

    temp = *x;
    *x = *y;
    *y = temp;
}