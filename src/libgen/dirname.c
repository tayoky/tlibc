#include <libgen.h>
#include <string.h>

char *dirname(char *path){
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

	if(!strchr(path,'/')){
		return ".";
	}

	//remove any trailing non slash
	strrchr(path,'/')[1] = '\0';

	
	//remove any trailing /
	end = &path[strlen(path)-1];
	while(end >= path && *end == '/'){
		*end = '\0';
		end--;
	}

	if(!*path){
		return "/";
	} else {
		return path;
	}
}
