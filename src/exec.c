#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <info.h> //get info on the current OS

extern char **environ;

//iplement all exec functions using execve

/// @brief convert an arg list 
/// @param arg0 first arg
/// @param args va_list of arg
/// @return an vector
static const char **ltov(const char *arg0,va_list args){
	int argc = 1;
	const char **argv = malloc(sizeof(char *));
	argv[0] = arg0;

	for(;;){
		char *arg = va_arg(args,char *);

		if(arg == NULL){
			break;	
		}

		argc++;
		argv = realloc(argv,sizeof(char *) * (argc + 1));
	}
	
	//last entry in argv is alaway NULL
	argv[argc] = NULL;
	return argv;
}

int execl(const char *pathname, const char *arg, ... /*, (char *) NULL */){
	va_list args;
	va_start(args,arg);
	const char **argv = ltov(arg,args);
	va_end(args);

	int ret = execv(pathname,(const char**)argv);
	free(argv);
	return ret;
}

int execlp(const char *file, const char *arg, ... /*, (char *) NULL */){
	va_list args;
	va_start(args,arg);
	const char **argv = ltov(arg,args);
	va_end(args);

	int ret = execvp(file,(const char**)argv);
	free(argv);
	return ret;
}

int execle(const char *pathname, const char *arg, ... /*, (char *) NULL, char *const envp[] */){
	(void)pathname;
	(void)arg;
	fprintf(stderr,"error : tlibc : call to execle stub\n");
	fflush(stderr);
	//TODO : make that
	return -ENOTSUP;
}

int execv(const char *pathname,const char *const argv[]){
	return execve(pathname,argv,(const char **)environ);
}

int execvp(const char *file,const char *const argv[]){
	return execvpe(file,argv,(const char **)environ);
}

int execvpe(const char *file,const char *const argv[],const char *const envp[]){
	//check if it is a normal path (contiain at least one '/')
	if(strchr(file,'/')){
		return execve(file,argv,envp);
	}

	//this is where the actual PATH work is done
	char *path = getenv("PATH");
	if(!path){
		//no path ?
		return -ENOENT;
	}

	//we are going to modify this
	path = strdup(path);

	size_t path_count = 1;

	//the separator is : on linux but ; on stanix
	for (size_t i = 0;path[i]; i++){
		if(path[i] == PATH_SEPARATOR){
			path_count++;
			path[i] = '\0';
		}
	}

	for (size_t i = 0; i < path_count; i++){
		//is what we search here ?
		char *full_filename = malloc(strlen(path) + strlen(file) + 2);
		sprintf(full_filename,"%s/%s",path,file);
		
		FILE *fd = fopen(full_filename,"r");
		if(fd){
			//we find it
			fclose(fd);
			int ret = execve(full_filename,argv,envp);
			free(full_filename);
			return ret;
		}
		free(full_filename);

		//go to the next one
		path += strlen(path) + 1;
	}

	free(path);

	//not found
	return -ENOENT;
}