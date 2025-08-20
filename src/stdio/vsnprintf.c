#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>
#include <string.h>
#include <sys/types.h>

#define OUT(c) *buf = c;\
buf++;\
count++;\
maxlen--;\
if(maxlen <= 0) return count

static int _print_uint(char *buf,size_t maxlen,uint64_t value,int base,int padding,char padding_char,int min,int high){
	char str[64];
	static char h[] = "0123456789ABCDEF";
	static char l[] = "0123456789abcdef";
	char *figures = high ? h : l;
	int count = 0;
	int i = 63;
	str[63] = '\0';
	while(value){
		i--;
		str[i] = figures[value % base];
		value /= base;
	}

	if(padding < 0){
		padding = -padding;
		while(padding > 63 - i && padding > min){
			padding--;
			OUT(padding_char);
		}
		padding = 0;
	}

	int len = 0;

	while(min > 63 - i){
		min--;
		len++;
		OUT('0');
	}
	
	while(str[i]){
		OUT(str[i]);
		len++;
		i++;
	}

	//print padding last if neccesary
	while(padding > len){
		padding--;
		OUT(padding_char);
	}

	return count;
}

#define print_uint(...) tmp = _print_uint(__VA_ARGS__);maxlen += tmp; count += tmp; buf += tmp

#define T(var,type) if(lenght == sizeof(type) && !parsed){\
		parsed = 1;\
		var = va_arg(args,type);\
	}

#define T_CAST(var,type) if(lenght == sizeof(type) && !parsed){\
		parsed = 1;\
		var = (type)va_arg(args,int);\
	}

int vsnprintf(char * buf,size_t maxlen, const char *fmt,va_list args){
	int count = 0;
	int tmp;
	while(*fmt){
		if(*fmt != '%'){
			OUT(*fmt);
			fmt++;
			continue;
		}
		fmt++;
		char positive_sign = '\0';
		char padding_char  = ' ';
		int padding_sign   = 1; //minus one mean left
		int alternate_form = 0;
		//format specifier
		//start by handling flags
		//TODO : #
		switch(*fmt){
		case '#':
			fmt++;
			alternate_form = 1;
			break;
		case '0':
			fmt++;
			if(padding_sign == -1)break;
			padding_char = '0';
			padding_sign = -1;
			break;
		case '-':
			fmt++;
			padding_char = ' ';
			padding_sign = -1;
			break;
		case ' ':
			fmt++;
			if(!positive_sign)positive_sign = ' ';
			break;
		case '+':
			fmt++;
			positive_sign = '+';
			break;
		default:
			goto finish_flags;
		}
finish_flags:;
		//now handle width
		int width = 0;
		if(*fmt == '*'){
			fmt++;
			width = va_arg(args,int);
			if(width < 0){
				width = -width;
				padding_sign = -padding_sign;
			}
		} else {
			while(isdigit(*fmt)){
				width *= 10;
				width += *fmt - '0';
				fmt++;
			}
		}
		//now we handle precision
		int precision = -1;
		if(*fmt == '.'){
			fmt++;
			if(*fmt == '*'){
				fmt++;
				precision = va_arg(args,int);
			} else {
				precision = 0;
				while(isdigit(*fmt)){
					precision *= 10;
					precision += *fmt - '0';
					fmt++;
				}
			}
		}
		//now lenght
		size_t lenght;
		switch(*fmt){
		default:
			lenght = sizeof(int);
			break;
		case 'h':
			fmt++;
			if(*fmt == 'h'){
				fmt++;
				lenght = sizeof(char);
			} else {
				lenght = sizeof(short);
			}
			break;
		case 'l':
			fmt++;
			if(*fmt == 'l'){
				fmt++;
				lenght = sizeof(long);
			} else {
				lenght = sizeof(long long);
			}
			break;
		case 'j':
			fmt++;
			lenght = sizeof(intmax_t);
			break;
		case 'z':
			fmt++;
			lenght = sizeof(size_t);
			break;
		case 't':
			fmt++;
			lenght = sizeof(ptrdiff_t);
			break;
		case 'L':
			//same as ll in this implementation
			fmt++;
			lenght = sizeof(long long);
			break;
		}
		//now specifier
		int parsed = 0;
		switch(*fmt){
		case 'd':
		case 'i':;
			intmax_t sint = 0;
			T(sint,int)
			T_CAST(sint,short)
			T_CAST(sint,char)
			T(sint,long)
			T(sint,long long)
			T(sint,intmax_t)
			T(sint,ssize_t)
			T(sint,ptrdiff_t)

			//turn into a uint so we can call print_uint
			if(sint < 0){
				sint = -sint;
				OUT('-');
			} else if(positive_sign){
				OUT(positive_sign);
			}
			print_uint(buf,maxlen,sint,10,width*padding_sign,padding_char,precision == -1 ? 1 : precision,0);
			break;
		case 'u':
		case 'o':
		case 'b':
		case 'x':
		case 'X':;
			intmax_t uint = 0;
			T(uint,unsigned int)
			T_CAST(uint,unsigned short)
			T_CAST(uint,unsigned char)
			T(uint,unsigned long)
			T(uint,unsigned long long)
			T(uint,uintmax_t)
			T(uint,size_t)
			T(uint,uintptr_t)

			if(positive_sign){
				OUT(positive_sign);
			}
			int base;
			switch(*fmt){
			case 'u':
				base = 10;
				break;
			case 'o':
				base = 8;
				if(alternate_form){
					OUT('0');
				}
				break;
			case 'b':
				base = 2;
				if(alternate_form){
					OUT('0');
					OUT('b');
				}
				break;
			case 'x':
			case 'X':
				base = 16;
				if(alternate_form){
					OUT('0');
					OUT(*fmt);
				}
				break;
			}
			print_uint(buf,maxlen,uint,base,width*padding_sign,padding_char,precision == -1 ? 1 : precision,*fmt == 'X');
			break;
		case 's':
		case 'c':;
			//TODO : wchar
			char *str;
			char ch;
			size_t len;
			if(*fmt == 'c'){
				len = 1;
				int c = va_arg(args,int);
				ch = (char)c;
				str = &ch;
			} else {
				str = va_arg(args,char *);
				len = strnlen(str,precision);
			}

			if(padding_sign == 1){
				while((size_t)width > len){
					OUT(padding_char);
					width--;
				}
			}
			for(size_t i=0; i<len; i++){
				OUT(*str);
				str++;
			}
			if(padding_sign == -1){
				while((size_t)width > len){
					OUT(padding_char);
					width--;
				}
			}
			break;
		case '%':
			OUT('%');
			break;
		}
		fmt++;
	
	}
	OUT('\0');
	return count;
}
