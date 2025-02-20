#include <ctype.h>

//TODO : isascii and toascii missing

int tolower(int C){
	if(isupper(C)){
		return C + 'a' - 'A';
	}
	return C;
}

int toupper(int c){
	if(islower(c)){
		return c + 'A' - 'a';
	}
	return c;
}

int islower(int c){
	return c >= 'a' && c <= 'z';
}

int isupper(int c){
	return c >= 'A' && c <= 'Z';
}

int isblank(int c){
	return isspace(c) || c == '\t';
}

int isspace(int c){
	return c == ' ';
}

int isdigit(int c){
	return c >= '0' && c <= '9';
}

int isxdigit(int c){
	c = tolower(c);
	return isdigit(c) || (c >= 'a' && c <= 'f');
}

int isalpha(int c){
	c = tolower(c);
	return c >= 'a' && c <= 'z';
}

int isalnum(int c){
	return isalpha(c) || isdigit(c);
}

int ispunct(int c){
	char *punct = "@&\"'()!-_,?;.:/=+^¨¨*$£`";
	while(*punct){
		if(*punct == c){
			return 1;
		}
		punct++;
	}
	return 0;
}

int iscntrl(int c){
	return c == '\b' || c == '\n';
}

int isgraph(int c){
	return isalnum(c) || ispunct(c);
}

int isprint(int c){
	return isgraph(c) || isspace(c);
}