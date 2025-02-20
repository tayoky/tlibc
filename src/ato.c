#include <stdlib.h>
#include <ctype.h>

long long int atoll(const char *str){
	char sign = 1;
	long long integer = 0;

	//ignore space
	while(isspace(*str)){
		if(!*str){
			//reach the end so 0
			return 0;
		}
		str++;
	}

	//handle negative numbers
	if(*str == '-'){
		sign = -1;
		str++;
	}

	//handle +
	if(*str == '+'){
		str++;
	}

	while(isdigit(*str)){
		integer *= 10;
		integer += (*str) - '0';
		str++;
	}

	return integer * sign;
}

long int atol(const char *str){
	return (long int)atoll(str);
}

int atoi(const char *str){
	return (int)atoll(str);
}

