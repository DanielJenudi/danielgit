/*****************************************************************************
 *Author: Daniel Jenudi
 *Reviewer: Mariana
 *Date: 22.08.22
 ******************************************************************************/

#include <stdio.h> /* fopen, fprintf, fclose */

#include "loger.h"

enum Ret_Val
{
    SUCCESS = 0,
    FAIL
};

int LogWrite(char *file_name, char *message)
{

    FILE *fp;
    static size_t s_log_number = 0;

    fp = fopen(file_name, "a");
    if (NULL == fp)
    {
        return FAIL;
    }

    ++s_log_number;
    fprintf(fp, "%ld - %s\n", s_log_number, message);
    fclose(fp);

    return SUCCESS;
}
