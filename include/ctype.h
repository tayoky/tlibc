#ifndef CTYPE_H
#define CTYPE_H

int tolower(int C);
int toupper(int c);

int islower(int c);
int isupper(int c);

int isspace(int c);
int isblank(int c);

int isdigit(int c);
int isxdigit(int c);
int isalpha(int c);
int ispunct(int c);

int iscntrl(int c);
int isgraph(int c);
int isprint(int c);

#endif