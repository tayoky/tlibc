#include <ctype.h>


int tolower(int C){
	if(C >= 'A' && C <= 'Z'){
		return C + 'a' - 'A';
	}
	return C;
}

int toupper(int c){
	if(c >= 'a' && c <= 'z'){
		return c + 'A' - 'a';
	}
	return c;
}