#include <stdlib.h> /* malloc, free, size_t */
#include <stdio.h>  /* printf */
#include <assert.h> /* assert */

void *AlignedMalloc(size_t bytes, size_t align);
void AlignedFree(void *ptr);

int main()
{
    void *ptr = AlignedMalloc(18, 32);
    printf("%ld\n", ((size_t)ptr % 16));
    AlignedFree(ptr);

    return 0;
}

void *AlignedMalloc(size_t bytes, size_t align)
{
    char *ptr = (char *)malloc(bytes + sizeof(size_t) + align);
    char *return_ptr = NULL;
    size_t align_address = 0;
    size_t align_dif = 0;

    assert(0 != bytes);

    align_address = ((size_t)ptr + (sizeof(size_t) + align - 1)) & ~(align - 1);
    align_dif = align_address - (size_t)ptr;

    return_ptr = ptr + align_dif;
    *(return_ptr - sizeof(size_t)) = align_dif;

    return return_ptr;
}

void AlignedFree(void *ptr)
{
    size_t gap_from_orig_ptr = 0;

    gap_from_orig_ptr = *((char *)ptr - sizeof(size_t));

    free(((char *)ptr - gap_from_orig_ptr));
}
