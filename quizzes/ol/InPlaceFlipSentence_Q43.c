#include <stdio.h>/* printf */
#include <stddef.h>/* size_t */
#include <assert.h>/* assert */


void ReversStr(char *str, size_t size);
static void Revers(char *str, size_t size);

int main()
{
    char str[] = "my name is daniel jenudi";
    size_t size = sizeof(str) * sizeof(char);

    printf("befor: %s\n", str);
    ReversStr(str, size);
    printf("after: %s\n", str);

    return 0;  
}

void ReversStr(char *str, size_t size)
{
    char *start_word = str;
    char *end_word = str;

    assert(NULL != str);
    assert(0 != size);

    while ('\0' != *end_word)
    {
        ++end_word;

        if(('\0' == *end_word) || (' ' == *end_word))
        {
            Revers(start_word, end_word - start_word);
            start_word = end_word + 1;
        }
    }
    
    Revers(str, size - 1);
}

static void Revers(char *str, size_t size)
{
    char *start = NULL;
    char *end = NULL;
    char temp = '\0';
    
    assert(NULL != str);
    assert(0 != size);

    start = str;
    end = str + size - 1;

    while(start < end)
    {
        temp = *start;
        *start = *end;
        *end = temp;

        ++start;
        --end;
    }
}