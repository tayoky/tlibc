#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdarg.h>
#include <limits.h>

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

static int print_uint(char *buf,size_t maxlen,uint64_t value,uint64_t base){
	char str[64];
	char figures[] = "0123456789ABCDEF";
	int count;
	uint64_t i = 63;
	str[63] = '\0';
	do{
		i--;
		str[i] = figures[value % base];
		value /= base;
	} while (value);
	
	size_t len = 0;
	while(str[i]){
		OUT(str[i]);
		len++;
		i++;
	}
	return len;
}

int vsnprintf(char * buf,size_t maxlen, const char *fmt,va_list args){
	int count = 0;
	while(*fmt){
		if(*fmt == '%'){
			fmt++;
			if(*fmt == 'c'){
				OUT(va_arg(args,int));
				fmt++;
			}
			if(*fmt == 's'){
				char *str = va_arg(args,char *);
				while(*str){
					OUT(*str);
					str++;
				}
			}
			if(*fmt == '%'){
				OUT('%');
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
					OUT('-');
					value = (uint64_t) -(int64_t)value;
				}
			case 'u':
				size = print_uint(buf,maxlen,value,10);
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
				size = print_uint(buf,maxlen,value,16);
				maxlen -= size;
				buf += size;
				count += size;
				if(maxlen <= 0){
					return count;
				}
				break;
			case 'o':
				size = print_uint(buf,maxlen,value,8);
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
	return count;
}