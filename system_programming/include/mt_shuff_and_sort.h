/*******************************************************************************
 * Name: Daniel Jenudi
 * Reviewer: Roni
 * Date: 10/07/22
 *******************************************************************************/
#ifndef __MT_SHUFF_AND_SORT_H__
#define __MT_SHUFF_AND_SORT_H__

#include <stddef.h> /* size_t */

enum Sort_Type
{
    BUBBLE_SORT = 0,
    QSORT = 1
};

int SortDic(unsigned char **arr, size_t arr_len, size_t threads_amount, int sort_type);

#endif /*__MT_SHUFF_AND_SORT_H__*/