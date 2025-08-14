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

#define strto(type,name,max,min) type name(const char *str, char **end, int base){\
	signed char sign = -1;\
	/* the sign might look wrong but it's actualy good\
	 * we keep the integer negative to avoid overflow */\
	type integer = 0;\
	if(end)*end = (char *)str;\
\
	if((base && base < 2) || base > 36){\
		errno = EINVAL;\
		return 0;\
	}\
	\
	/*ignore space*/\
	while(isspace(*str))str++;\
\
	/*handle negative numbers*/\
	switch (*str){\
	case '-':\
		sign = 1;\
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
	/* thanks dcraftbg for the overflow handling idea */\
	while(char2digit(*str) < base){\
		type save = integer;\
		integer *= base;\
		integer -= char2digit(*str);\
		if((integer + char2digit(*str)) / base != save){\
			/*overflow*/\
			errno = ERANGE;\
			return sign == -1 ? max : min;\
		}\
		str++;\
		if(end)*end = (char *)str;\
	}\
\
	if(sign == -1 && integer == min){\
		/* overflow */\
		errno = ERANGE;\
		return max;\
	}\
	return integer * sign;\
}

#define strtou(type,name,max) type name(const char *str, char **end, int base){\
	type integer = 0;\
	if(end)*end = (char *)str;\
\
	if((base && base < 2 ) || base > 36){\
		errno = EINVAL;\
		return 0;\
	}\
	\
	/*ignore space*/\
	while(isspace(*str))str++;\
\
	/*handle negative numbers*/\
	switch (*str){\
	case '-':\
		 errno = ERANGE;\
		 return 0;\
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
	/* thanks dcraftbg for the overflow handling idea */\
	while(char2digit(*str) < base){\
		type save = integer;\
		integer *= base;\
		integer += char2digit(*str);\
		if((integer - char2digit(*str)) / base != save){\
			/*overflow*/\
			errno = ERANGE;\
			return max;\
		}\
		str++;\
		if(end)*end = (char *)str;\
	}\
\
	return integer;\
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
