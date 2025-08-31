#include <string.h>

char *strstr(const char *str1,const char *str2){
	size_t str2_len = strlen(str2) + 1;
	do{
		//check all char
		for(size_t i=0;i<str2_len;i++){
			if(!str2[i]){
				//all str2 was found
				return (char *)str1;
			}

			if(str1[i] != str2[i]){
				break;
			}
		}
	}while(*(str1++));
	return NULL;
}
