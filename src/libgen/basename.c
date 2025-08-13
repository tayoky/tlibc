#include <libgen.h>
#include <string.h>

char *basename(char *path){
	//special case : "" should return "."
	if(!path ||!strcmp(path,"")){
		return ".";
	}

	//remove any trailing / except if the first char is an /
	char *end = &path[strlen(path)-1];
	while(end > path && *end == '/'){
		*end = '\0';
		end--;
	}

	//now we have simplifed path
	// "/usr/lib////" -> "/usr/lib"
	// "///" -> "/"
	//if it's only one char or it don't contain any /
	//we can return the entrire string

	//we use strchr the first time cause it's faster
	if(strchr(path,'/') && path[1]){
		return strrchr(path,'/') + 1;
	} else {
		return path;
	}
}
