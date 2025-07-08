#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <limits.h>

int fgetc(FILE *stream){
	unsigned char c = 0;
	return fread(&c,sizeof(c),1,stream) ? c : EOF;
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
	return fwrite(&c,sizeof(c),1,stream) ? lc : EOF;
}

int putc(int c,FILE *stream){
	return fputc(c,stream);
}

int putchar(int c){
	return fputc(c,stdout);
}

int fputs(const char *str,FILE *stream){
	return fwrite(str,sizeof(char),strlen(str),stream) ? 0 : -1;
}

int puts(const char *str){
	if(fputs(str,stdout) < 0){
		return -1;
	}
	return putchar('\n') != EOF ? 0 : -1 ;
}
