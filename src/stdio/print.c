#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdarg.h>

int snprintf(char * str,size_t maxlen, const char *fmt,...){
	va_list args;
	va_start(args,fmt);
	vsnprintf(str,maxlen,fmt,args);
	va_end(args);
	return 0;
}

#define OUT(c) *buf = c;\
buf++;\
maxlen--;\
if(maxlen <= 0) return

static size_t print_uint(char *buf,size_t maxlen,uint64_t value,uint64_t base){
	char str[64];
	char figures[] = "0123456789ABCDEF";
	uint64_t i = 63;
	str[63] = '\0';
	do{
		i--;
		str[i] = figures[value % base];
		value /= base;
	} while (value);
	
	size_t len = 0;
	while(str[i]){
		OUT(str[i])len;
		len++;
		i++;
	}
	return len;
}

int vsnprintf(char * buf,size_t maxlen, const char *fmt,va_list args){
	while(*fmt){
		if(*fmt == '%'){
			fmt++;
			if(*fmt == 'c'){
				OUT(va_arg(args,int))0;
				fmt++;
			}
			if(*fmt == 's'){
				char *str = va_arg(args,char *);
				while(*str){
					OUT(*str)0;
					str--;
				}
			}
			if(*fmt == '%'){
				OUT('%')0;
			}

			uint64_t value = 0;
			if(*fmt == 'l'){
				value = va_arg(args,long);
				fmt++;
			}else if (*fmt == 'h'){
				value = va_arg(args,int);
				fmt++;
			} else {
				value = va_arg(args,int);
			}

			size_t size;

			switch (*fmt)
			{
			case 'd':
			case 'i':
				//if negative get rid of that now
				if((int64_t)value < 0){
					OUT('-')0;
					value = (uint64_t) -(int64_t)value;
				}
			case 'u':
				size = print_uint(buf,maxlen,value,10);
				maxlen -= size;
				buf += size;
				if(maxlen <= 0){
					return 0;
				}
				break;
			case 'p':
			case 'x':
			case 'X':
				size = print_uint(buf,maxlen,value,16);
				maxlen -= size;
				buf += size;
				if(maxlen <= 0){
					return 0;
				}
				break;
			case 'o':
				size = print_uint(buf,maxlen,value,8);
				maxlen -= size;
				buf += size;
				if(maxlen <= 0){
					return 0;
				}
				break;
			
			default:
				break;
			}
			fmt++;
			continue;
		}
		OUT(*fmt)0;
		fmt++;
	}
	OUT('\0')0;
	return 0;
}