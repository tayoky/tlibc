#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/type.h>

int sprintf(char * str,const char *fmt,...){
	va_list args;
	va_start(args,fmt);
	int ret = vsprintf(str,fmt,args);
	va_end(args);
	return ret;
}
int vsprintf(char * buf,const char *fmt,va_list args){
	return vsnprintf(buf,INT_MAX,fmt,args);
}


int snprintf(char * str,size_t maxlen, const char *fmt,...){
	va_list args;
	va_start(args,fmt);
	int ret = vsnprintf(str,maxlen,fmt,args);
	va_end(args);
	return ret;
}

#define OUT(c) *buf = c;\
buf++;\
count++;\
maxlen--;\
if(maxlen <= 0) return count

static int print_uint(char *buf,size_t maxlen,uint64_t value,uint64_t base,ssize_t padding,char padding_char){
	char str[64];
	memset(str,padding_char,64);
	static char figures[] = "0123456789ABCDEF";
	int count = 0;
	uint64_t i = 63;
	str[63] = '\0';
	do{
		i--;
		str[i] = figures[value % base];
		value /= base;
	} while (value);

	if(padding > 0 && (63 - padding) < (ssize_t)i){
		i = 63 - padding;
	}
	
	size_t len = 0;
	while(str[i]){
		OUT(str[i]);
		len++;
		i++;
	}

	//print padding last if neccesary
	if(padding < 0 && -padding > (ssize_t)len){
		padding = -padding;
		padding -= len;
		while(padding > 0){
			OUT(padding_char);
			padding--;
		}
	}

	return len;
}

int vsnprintf(char * buf,size_t maxlen, const char *fmt,va_list args){
	int count = 0;
	while(*fmt){
		if(*fmt == '%'){
			fmt++;

			//default padding
			char padding_char = ' ';
			ssize_t padding = 0;

			switch(*fmt){
			case ' ':
			case '0':
				padding_char = *fmt;
				fmt++;
				break;
			}

			//read the padding
			int sign = 1;
			switch(*fmt ){
			case '-':
				sign = -1;
				fmt++;
				break;
			case '*':
				padding = va_arg(args,int);
				fmt++;
				goto skip_padding_read;
			}
			while(isdigit(*fmt)){
				padding *= 10;
				padding += (*fmt) - '0';
				fmt++;
			}
			padding *= sign;
			skip_padding_read:

			//not integer cases
			switch(*fmt){
			case 'c':
				while(padding > 1){
					OUT(padding_char);
					padding--;
				}
				OUT(va_arg(args,int));
				while(padding < -1){
					OUT(padding_char);
					padding++;
				}
				fmt++;
				continue;
			case 's':
				;char *str = va_arg(args,char *);
				size_t str_len = strlen(str);

				//print padding first if neccesary
				if(padding > 0 && padding > (ssize_t)str_len){
					padding -= str_len;
					while(padding > 0){
						OUT(padding_char);
						padding--;
					}
				}

				//print the string
				while(*str){
					OUT(*str);
					str++;
				}

				//print padding last if neccesary
				if(padding < 0 && -padding > (ssize_t)str_len){
					padding = -padding;
					padding -= str_len;
					while(padding > 0){
						OUT(padding_char);
						padding--;
					}
				}

				fmt++;
				continue;
			case '%':
				OUT('%');
				fmt++;
				continue;
			}

			//it's an integer
			uint64_t value = 0;
			switch(*fmt){
			case 'l':
				fmt++;
				if(*fmt == 'l'){
					fmt++;
					value = va_arg(args,long long);
					break;
				}
				value = va_arg(args,long);
				break;
			case 'h':
				value = va_arg(args,int);
				fmt++;
				break;
			default:
				value = va_arg(args,int);
				break;
			}

			size_t size;

			switch (*fmt)
			{
			case 'd':
			case 'i':
				//if negative get rid of that now
				if((int64_t)value < 0){
					OUT('-');
					value = (uint64_t) -(int64_t)value;
				}
				//fallthrough
			case 'u':
				size = print_uint(buf,maxlen,value,10,padding,padding_char);
				maxlen -= size;
				buf += size;
				count += size;
				if(maxlen <= 0){
					return count;
				}
				break;
			case 'p':
			case 'x':
			case 'X':
				size = print_uint(buf,maxlen,value,16,padding,padding_char);
				maxlen -= size;
				buf += size;
				count += size;
				if(maxlen <= 0){
					return count;
				}
				break;
			case 'o':
				size = print_uint(buf,maxlen,value,8,padding,padding_char);
				maxlen -= size;
				buf += size;
				count += size;
				if(maxlen <= 0){
					return count;
				}
				break;
			
			default:
				break;
			}
			fmt++;
			continue;
		}
		OUT(*fmt);
		fmt++;
	}
	OUT('\0');
	return count - 1; //don't count the last '\0'
}
