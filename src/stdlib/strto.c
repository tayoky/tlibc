#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>

static int char2digit(char c){
	if(c >= '0' && c <= '9')return c - '0';
	if(c >= 'A' && c <= 'Z')return c - 'A' + 10;
	if(c >= 'a' && c <= 'z')return c - 'a' + 10;
	return INT_MAX;
}

#define strto(type,name,max,min) type name(const char *str, char **end, int base){\
	signed char sign = 1;\
	type integer = 0;\
	if(end)*end = (char *)str;\
\
	if((base && base < 2) || base > 36){\
		errno = EINVAL;\
		return 0;\
	}\
	\
	while(isspace(*str))str++;\
\
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
		if(!strncasecmp(str,"0b",2)&& char2digit(str[2]) < 2)str+=2;\
		break;\
	case 8:\
		if(!strncasecmp(str,"0",1)&& char2digit(str[1]) < 8)str++;\
		break;\
	case 16:\
		if(!strncasecmp(str,"0x",2) && char2digit(str[2]) < 16)str+=2;\
		break;\
	}\
\
	/* thanks dcraftbg for the overflow handling idea */\
	while(char2digit(*str) < base){\
		if(end)*end = (char *)str+1;\
		if(integer * base / base != integer){\
			/*overflow*/\
			errno = ERANGE;\
			return sign == 1 ? max : min;\
		}\
		integer *= base;\
		if((sign == 1 && max - integer  < char2digit(*str)) ||  (sign == -1 && min - integer  > -char2digit(*str))){\
			/*overflow*/\
			errno = ERANGE;\
			return sign == 1 ? max : min;\
		}\
		integer += sign * char2digit(*str);\
		str++;\
	}\
\
	return integer;\
}

#define strtou(type,name,max) type name(const char *str, char **end, int base){\
	signed char sign = 1;\
	type integer = 0;\
	if(end)*end = (char *)str;\
\
	if((base && base < 2 ) || base > 36){\
		errno = EINVAL;\
		return 0;\
	}\
	\
	while(isspace(*str))str++;\
\
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
		if(!strncasecmp(str,"0b",2)&& char2digit(str[2]) < 2)str+=2;\
		break;\
	case 8:\
		if(!strncasecmp(str,"0",1)&& char2digit(str[1]) < 8)str++;\
		break;\
	case 16:\
		if(!strncasecmp(str,"0x",2) && char2digit(str[2]) < 16)str+=2;\
		break;\
	}\
\
	/* thanks dcraftbg for the overflow handling idea */\
	while(char2digit(*str) < base){\
		if(end)*end = (char *)str+1;\
		if(integer * base / base != integer){\
			/*overflow*/\
			errno = ERANGE;\
			return max;\
		}\
		integer *= base;\
		if(integer + char2digit(*str) < integer){\
			/*overflow*/\
			errno = ERANGE;\
			return max;\
		}\
		integer += char2digit(*str);\
		str++;\
	}\
\
	return sign == 1 ? integer : max - integer + 1;\
}

//it support both . and , 
#define strtd(type,name) type name(const char *str, char **end){\
	long long integer = 0;\
	long long pow = 0;\
	signed char sign = 1;\
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

strto(long,strtol,LONG_MAX,LONG_MIN)
strto(long long,strtoll,LLONG_MAX,LLONG_MIN)
strtou(unsigned long,strtoul,ULONG_MAX)
strtou(unsigned long long,strtoull,ULLONG_MAX)
strtd(float,strtof)
strtd(double,strtod)
strtd(long double,strtold)
