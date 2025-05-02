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

//it support both . and , 
#define strtd(type,name) type name(const char *str, char **end){\
	long long integer = 0;\
	long long pow = 0;\
	char sign = 1;\
	if(end) *end = (char *)str;\
\
	/*ignore space*/\
	while(isspace(*str)){\
		if(!*str){\
			return 0;\
		}\
		str++;\
	}\
\
	/*handle + and -*/\
	switch (*str){\
	case '-':\
		sign = -1;\
		/*fallthrough*/\
	case '+':\
		str++;\
		break;\
	\
	default:\
		break;\
	}\
\
	/*find the divisor and base number*/\
	while(*str){\
		if(isdigit(*str)){\
			pow *= 10;\
			integer *= 10;\
			integer += (*str) - '0';\
		} else if (*str == '.' || *str == ','){\
			pow = 1;\
		} else {\
			break;\
		}\
		str++;\
		if(end) *end = (char *)str;\
	}\
	integer *= sign;\
	if(pow == 0){\
		pow = 1;\
	}\
\
	/*TODO : add exposant support here*/\
\
	return (type)integer/(type)pow;\
}

strto(long,strtol)
strto(long long,strtoll)
strto(unsigned long,strtoul)
strto(unsigned long long,strtoull)
strtd(float,strtof)
strtd(double,strtod)
strtd(long double,strtold)
