#ifndef __MT_COUNTING_SORT_H__
#define __MT_COUNTING_SORT_H__

#include <stddef.h> /* size_t */

int MtCountingSort(unsigned char *arr, size_t len, size_t threads_amount);

#endif /*__MT_COUNTING_SORT_H__*/