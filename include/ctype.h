#ifndef _CTYPE_H
#define _CTYPE_H

#include <features.h>

int tolower(int c);
int toupper(int c);
int toascii(int c);

int islower(int c);
int isupper(int c);
#if (defined(_XOPEN_SOURCE) && _XOPEN_SOURCE) || (defined(_DEFAULT_SOURCE) || _DEFAULT_SOURCE)
int isascii(int c);
#endif

int isspace(int c);
#if (defined(_ISOC99_SOURCE) && _ISOC99_SOURCE) || (defined(_POSIX_C_SOURCE) || _POSIX_C_SOURCE >= 200112L)
int isblank(int c);
#endif

int isdigit(int c);
int isxdigit(int c);
int isalpha(int c);
int isalnum(int c);
int ispunct(int c);

int iscntrl(int c);
int isgraph(int c);
int isprint(int c);

#endif
