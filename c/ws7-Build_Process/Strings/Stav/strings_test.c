/***************************************
*Name : Stav Ben Shushan		 *			 
*Date: 8.2.22				 *
*File:					 *
*Description : test punctions of string *
***************************************/

#include <stdio.h>
/* printf */
#include <string.h>
#include <strings.h>
/* strlen */
#include "strings.h"
/* strlen */
#include <ctype.h>
/*isupper*/
#include <stdlib.h>
/*malloc*/
#include <assert.h>

int main()
{
	char st[12] = {"Hello"};
	char st2[12] = {"HeLlo"};
	char st3[] = {"hafsyhfvrs"};
	char st4[12] = {"fr"};
	char st5[20] = {"Hello"};
	char st6[] = {"aLl"};
	char st7[] = {""};
	char st8[] = "find shiduch for Stav Ben Shushan";
	char st9[] = "av ygfwe";
	char st10[] = "abf";
	const char st11[] = "Have a good day"; 
	char *ret = strstr(st8, st9);
	char *target = StrDup(st5);
	int num=2;
	int num2=0;

	/*char src[50]= "Sparta";
	char dest[50] = "This is ";
	printf("Final destination string : |%s|\n", StrnCat(dest, src, 3));*/

	 
	

	/*StrLen test
	printf("REALL : %ld\n", strlen (st8));
	printf("MY    : %ld\n", StrLen (st8));
	printf("REALL : %ld\n", strlen (st10));
	printf("MY    : %ld\n", StrLen (st10));
	printf("REALL : %ld\n", strlen (st3));
	printf("MY    : %ld\n", StrLen (st3));
	printf("REALL : %ld\n", strlen (st7));
	printf("MY    : %ld\n", StrLen (st7));*/
	
	/*StrCmp test
	printf("st BEFORE %s\n" , st);
	printf("st2 BEFORE %s\n" , st2);
	printf("st5 BEFORE %s\n" , st5);
	printf("st6 BEFORE %s\n" , st6);
	printf("st7 BEFORE %s\n" , st7);
	printf("REALL : %d\n", strcmp (st , st2));
	printf("MY    : %d\n", StrCmp (st , st2));
	printf("REALL : %d\n", strcmp (st , st5));
	printf("MY    : %d\n", StrCmp (st , st5));
	printf("REALL : %d\n", strcmp (st , st7));
	printf("MY    : %d\n", StrCmp (st , st7));
	printf("REALL : %d\n", strcmp (st , st6));
	printf("MY    : %d\n", StrCmp (st , st6));
	printf("st AFTER %s\n" , st);
	printf("st2 AFTER %s\n" , st2);
	printf("st5 AFTER %s\n" , st5);
	printf("st6 AFTER %s\n" , st6);
	printf("st7 AFTER %s\n" , st7);*/
	
	/*StrnCmp test*/
	
	/*printf("REALL : %d\n", strncmp (st , st2,num));
	printf("MY    : %d\n", StrnCmp (st , st2,num));
	printf("REALL : %d\n", strncmp (st , st5,num));
	printf("MY    : %d\n", StrnCmp (st , st5,num));
	printf("REALL : %d\n", strncmp (st , st7,num));
	printf("MY    : %d\n", StrnCmp (st , st7,num));
	printf("REALL : %d\n", strncmp (st , st6,num));
	printf("MY    : %d\n", StrnCmp (st , st6,num));*/
	
	/*StrCaseCmp test*/
	
	/*printf("REALL : %d\n", strcasecmp (st , st2));
	printf("MY    : %d\n", StrCasecmp (st , st2));
	printf("REALL : %d\n", strcasecmp (st , st5));
	printf("MY    : %d\n", StrCasecmp (st , st5));
	printf("REALL : %d\n", strcasecmp (st , st7));
	printf("MY    : %d\n", StrCasecmp (st , st7));
	printf("REALL : %d\n", strcasecmp (st , st6));
	printf("MY    : %d\n", StrCasecmp (st , st6));
	printf("REALL : %d\n", strcasecmp (st , st8));
	printf("MY    : %d\n", StrCasecmp (st , st8));*/
	 
	 
	/*StrCat test*/
	/*printf("REALL : %s\n", strcat (st5 , st4));
	printf("MY    : %s\n", StrCat (st5 , st4));
	printf("REALL : %s\n", strcat (st5 , st7));
	printf("MY    : %s\n", StrCat (st5 , st7));
	printf("REALL : %s\n", strcat (st , st6));
	printf("MY    : %s\n", StrCat (st , st6));*/
	
	/*StrnCat test*/
	/*printf("REALL : %s\n", strncat (st5 , st4, 1));
	printf("MY    : %s\n", StrnCat (st5 , st4, 1));
	printf("REALL : %s\n", strncat (st5 , st7, 3));
	printf("MY    : %s\n", StrnCat (st5 , st7, 3));
	printf("REALL : %s\n", strncat (st , st6 , 5));
	printf("MY    : %s\n", StrnCat (st , st6, 5));*/
	
	/*StrStr test*/
	/*printf("REALL : %s\n", strstr (st8 , st9));
	printf("MY    : %s\n", StrStr (st8 , st9));
	printf("REALL : %s\n", strstr (st8 , st10));
	printf("MY    : %s\n", StrStr (st8 , st10));
	printf("REALL : %s\n", strstr (st , st5));
	printf("MY    : %s\n", StrStr (st , st5));
	printf("REALL : %s\n", strstr (st3 , st4));
	printf("MY    : %s\n", StrStr (st3 , st4));
	printf("REALL : %s\n", strstr (st5 , st7));
	printf("MY    : %s\n", StrStr (st5 , st7));*/
	
	/*Strspn test
	printf("REALL : %ld\n", strspn (st8 , st10));
	printf("MY    : %ld\n", StrSpn (st8 , st10));
	printf("REALL : %ld\n", strspn (st8 , st4));
	printf("MY    : %ld\n", StrSpn (st8 , st4));
	printf("REALL : %ld\n", strspn (st6 , st7));
	printf("MY    : %ld\n", StrSpn (st6 , st7));
	printf("REALL : %ld\n", strspn (st9 , st3));
	printf("MY    : %ld\n", StrSpn (st9 , st3));*/
	
	/*StrChr test*/
	/*printf("MY    : %s\n", StrChr (st8 , 'h'));
	printf("REALL : %s\n", strchr (st8 , 'h'));
	printf("MY    : %s\n", StrChr (st10 , 'b'));
	printf("REALL : %s\n", strchr (st10 , 'b'));
	printf("MY    : %s\n", StrChr (st4 , 'f'));
	printf("REALL : %s\n", strchr (st4 , 'f'));
	printf("MY    : %s\n", StrChr (st7 , 'b'));
	printf("REALL : %s\n", strchr (st7 , 'b'));*/
	
	/*StrDup*/
	printf("MY    : %s\n", target);	
	free (target);
	
	return 0;
}





