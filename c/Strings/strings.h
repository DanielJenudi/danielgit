#include <stddef.h>

/*#include "strings.c"*/
#ifndef __ILRD_STRINGS_H__
#define __ILRD_STRINGS_H__

size_t StrLen(const char *str);
int StrCmp(const char *str1, const char *str2);
char *StrCpy (char *dest, const char *src);
char *StrnCpy(char *dest, const char *src, size_t n);
int StrnCmp(const char *str1, const char *str2, size_t n);
int StrCasecmp(const char *str1, const char *str2);
char *StrChr(const char *str, int c);
char *StrDup(const char *str1);
char *StrCat(char *dest, const char *src);
char *StrnCat(char *dest, const char *src, size_t n);
char *StrStr(const char *haystack, const char *needle);
size_t StrSpn(const char *str1, const char *str2);
char *StrTok(char *str, const char *delim);


#endif /*__ILRD_STRINGS_H__*/
