#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <stdint.h>

int vsscanf(const char *buf,const char *fmt,va_list args){
	int n = 0;

	while(*fmt){
		switch(*fmt){
		case ' ':
			//skip any spaces
			while(isspace(*buf))buf++;
			break;
		case '%':
			fmt++;
			int is_long = 0;
			char *end;
			switch(*fmt){
			case 'c':
				fmt++;
				if(!*buf) return n;
				*va_arg(args,char *) = *buf;
				n++;
				buf++;
				break;
			case 's':
				fmt++;
				//HOLY SHIT this is extremly unsafe
				char *str = va_arg(args,char *);
				while(!(isblank(*buf) || *buf == '\n' || !*buf)){
					*str = *buf;
					buf++;
					str++;
				}
				*str = '\0';
				n++;
				break;
			case 'p':
				fmt++;
				uintptr_t ptr = strtol(buf,&end,16);
				if(end == buf){
					//failed to read so no more data or it's not an ptr
					return n;
				}
				*va_arg(args,uintptr_t *) = ptr;
				buf = end;
				break;
			case 'l':
				fmt++;
				is_long = 1;
				//fallthrough
			case 'd':
			case 'f':
				switch(*fmt){
				case 'd':
					;long integer = strtol(buf,&end,0);
					if(end == buf){
						return n;
					}
					buf = end;
					if(is_long){
						*va_arg(args,long *) = integer;
					} else {
						*va_arg(args,int *) = (int)integer;
					}
					break;
				case 'f':
					;double flot = strtod(buf,&end);
					if(end == buf){
						return n;
					}
					buf = end;
					if(is_long){
						*va_arg(args,double *) = flot;
					} else {
						*va_arg(args,float *) = (float)flot;
					}
					break;
				default :
					return n;
				}
				fmt++;
				break;
			default :
				//unknow, so fail ... i guess ???
				return n;
			}
			break;
		default :
			//except exact char
			if(*fmt != * buf){
				return n;
			}
			buf++;
			break;
		}
		fmt++;
	}

	return n;
}

int sscanf(const char *buf,char *fmt,...){
	va_list args;
	va_start(args,fmt);
	int ret = vsscanf(buf,fmt,args);
	va_end(args);
	return ret;
}
