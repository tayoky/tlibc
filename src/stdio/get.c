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
		stream->errno = errno;
		//we normally return -1 on error
		//but here -1 is EOF
		return -2;
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
	return fgetc(stdin);
}

char *fgets(char *string, int n, FILE *stream){
	//read until '\n'
	int c = 0;
	do {
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


int fputc(int lc,FILE *stream){
	unsigned char c = (unsigned char)lc;
	if(write(stream->fd,&c,1) < 0){
		stream->errno = errno;
		return -1;
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
		stream->errno = errno;
		return -1;
	}
	return 0;
}

int puts(char *string){
	if(fputs(string,stdout) < 0){
		return -1;
	}
	return putchar('\n');
}
