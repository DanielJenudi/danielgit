#include <stdio.h>



int main()
{
    char arr[] = {0x40, 0x50, 0x60, 0x70, 0x80, 0x81, 0x82, 0x83};
    char result = '0';
    unsigned long num = *(unsigned long *)arr;
    short *sptr = (short *)&num;
    sptr += (sizeof(num) >> 2);
    result = *sptr;
    
    printf("%d\n", result);

    return 0;
}

