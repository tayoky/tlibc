#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>
#include <string.h>

static int char2digit(char c){
	if(c >= '0' && c <= '9')return c - '0';
	if(c >= 'A' && c <= 'Z')return c - 'A' + 10;
	if(c >= 'a' && c <= 'z')return c - 'a' + 10;
	return INT_MAX;
}

#define strto(type,name) type name(const char *str, char **end, int base){\
	char sign = 1;\
	type integer = 0;\
	if(end)*end = (char *)str;\
\
	if(base >= 26){\
		errno = EINVAL;\
		return 0;\
	}\
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
	switch(base){\
	case 0:\
		if(*str == '0'){\
			str++;\
			switch(*str){\
			case 'x':\
			case 'X':\
				base = 16;\
				str++;\
				break;\
			case 'b':\
				base = 2;\
				str++;\
				break;\
			default:\
				base = 8;\
				break;\
			}\
		} else {\
			base = 10;\
		}\
		break;\
	case 2:\
		if(!strcmp(str,"0b"))str+=2;\
		break;\
	case 8:\
		if(!strcmp(str,"0"))str++;\
		break;\
	case 16:\
		if(!strcmp(str,"0x"))str+=2;\
		break;\
	}\
\
	while(char2digit(*str) < base){\
		integer *= base;\
		integer += char2digit(*str);\
		str++;\
		if(end)*end = (char *)str;\
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
