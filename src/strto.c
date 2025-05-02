#include <stdlib.h>
#include <limits.h>
#include <ctype.h>
#include <string.h>

static int char2digit(char c){
	if(c >= '0' && c <= '9')return c - '0';
	if(c >= 'A' && c <= 'Z')return c - 'A';
	if(c >= 'a' && c <= 'z')return c - 'a';
	return INT_MAX;
}

#define strto(type,name) type name(const char *str, char **end, int base){\
	char sign = 1;\
	type integer = 0;\
	if(end)*end = (char *)str;\
\
	/*ignore space*/\
	while(isspace(*str)){\
		if(!*str){\
			/*reach the end so 0*/\
			return 0;\
		}\
		str++;\
	}\
\
	/*handle negative numbers*/\
	switch (*str){\
	case '-':\
		sign = -1;\
		/*fallthrough*/\
	case '+':\
		str++;\
		break;\
	}\
	/*automatic base*/\
	if(base == 0){\
		if(!strcmp("0x",str)) base = 16;\
		else if(!strcmp("0X",str)) base = 16;\
		else if(!strcmp("0b",str)) base = 2;\
		else if(!strcmp("0",str))  base = 8;\
		base = 10;\
	}\
\
	while(char2digit(*str) < base){\
		integer *= base;\
		integer += char2digit(*str);\
		if(end)*end = (char *)str;\
		str++;\
	}\
\
	return integer * sign;\
}

strto(long,strtol)
strto(long long,strtoll)
strto(unsigned long,strtoul)
strto(unsigned long long,strtoull)
