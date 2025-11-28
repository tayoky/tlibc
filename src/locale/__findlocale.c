#include <locale.h>
#include <stdlib.h>
#include <string.h>

struct __locale_data *__findlocale(const char *name){
	if(name[0] == '\0'){
		//no name ??? try to get from environ
		if(getenv("LC_ALL")){
			name = getenv("LC_ALL");
		} else if(getenv("LANG")){
			name = getenv("LANG");
		} else {
			name = "POSIX";
		}
	}

	if (!strcmp(name, "POSIX")) return (struct __locale_data*)&__posix;
	if (!strcmp(name, "C")) return (struct __locale_data*)&__posix;
	return NULL;
}
