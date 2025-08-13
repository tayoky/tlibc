#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//really bad realpath pls don't look at it
char *realpath(const char *path,char *resolved_path){
	if(path[0] == '/'){
		if(resolved_path){
			return strcpy(resolved_path,path);
		} else {
			return strdup(path);
		}
	}

	//we need to get cwd
	char *cwd = malloc(256);
	if(getcwd(cwd,256)){
		free(cwd);
		return NULL;
	}
	//if cwd is "/" convert to ""
	if(!strcmp(cwd,"")){
		free(cwd);
		cwd = strdup("");
		if(!cwd){
			return NULL;
		}
	}

	
	if(!resolved_path){
		resolved_path = malloc(strlen(cwd) + strlen(path) + 2);
		if(!resolved_path){
			free(cwd);
			return NULL;
		}
	}

	//good now put the two togher
	strcpy(resolved_path,cwd);
	strcat(resolved_path,cwd);

	return resolved_path;
}