#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stddef.h>
#include <string.h>
#include <limits.h>
#undef errno

struct _FILE{
	int fd;
	long errno;
	int eof;
};

int fgetc(FILE *stream){
 	unsigned char c = 0;
	ssize_t rsize = read(stream->fd,&c,1);
	if(rsize < 0){
		return __set_errno(rsize);
	}
	if(rsize == 0){
		stream->eof = 1;
		return EOF;
	}
	return c;
}
int getc(FILE *stream){
	return fgetc(stream);
}
int getchar(void){
	return(fgetc(stdin));
}

char *fgets(char *string, int n, FILE *stream){
	//read until '\n'
	int c = 0;
	do
	{
		if(n <= 1){
			break;
		}
		c = fgetc(stream);

		//if EOF quit immediatlely
		if(c == EOF){
			break;
		}

		*string = (char)c;
		string++;
		n--;
	} while (c != '\n');

	*string = '\0';
	return string;
}
char *gets(char *buffer){
	return fgets(buffer,INT_MAX,stdin);
}



int fputc(int c,FILE *stream){
	ssize_t wsize = write(stream->fd,&c,1);
	if(wsize < 0){
		return __set_errno(wsize);
	}
	return 0;
}
int putc(int c,FILE *stream){
	return fputc(c,stream);
}
int putchar(int c){
	return fputc(c,stdout);
}

int fputs(char *string,FILE *stream){
	if(write(stream->fd,string,strlen(string)) < 0){
		return -1;
	}
	return 0;
}
int puts(char *string){
	if(write(stdout->fd,string,strlen(string)) < 0){
		return -1;
	}
	if(putchar('\n') < 0){
		return -1;
	}
	return 0;
}