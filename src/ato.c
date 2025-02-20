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

double atof(const char *str){
	long long integer = 0;
	long long pow = 0;
	char sign = 1;

	//ignore space
	while(isspace(*str)){
		if(!*str){
			return 0;
		}
		str++;
	}

	//handle + and -
	if(*str == '-'){
		sign = -1;
		str++;
	}
	if(*str == '+'){
		sign = 1;
		str++;
	}

	//find the divisor and base number
	while(*str){
		if(isdigit(*str)){
			pow *= 10;
			integer *= 10;
			integer += (*str) - '0';
		} else if (*str == '.' || *str == ','){
			pow = 1;
		} else {
			break;
		}
		str++;
	}
	integer *= sign;
	if(pow == 0){
		pow = 1;
	}

	//TODO : add exposant support here

	return (double)integer/(double)pow;
}