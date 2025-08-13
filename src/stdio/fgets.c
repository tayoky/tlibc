#include <stdio.h>

char *fgets(char *string, int n, FILE *stream){
	//read until '\n'
	int c = 0;
	do {
		if(n <= 0){
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

	if(n >= 1)*string = '\0';
	return string;
}
