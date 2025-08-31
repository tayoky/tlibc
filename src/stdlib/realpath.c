#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

#if defined(LIBK) && defined(__stanix__)
#include <kernel/scheduler.h>
#endif

char *realpath(const char *path,char *resolved_path){

	//first let make an absolute path
	char *abs;
	if(path[0] == '/'){
		abs = strdup(path);
		if(!abs)return NULL;
	} else {
		//relative path
#if defined(LIBK) && defined(__stanix__)
		char *cwd = get_current_proc()->cwd_path;
#else
		char cwd[256];
		if(!getcwd(cwd,sizeof(cwd)))return NULL;
#endif
		abs = malloc(strlen(cwd) + strlen(path) + 2);
		if(!abs)return NULL;

		//now put the two togher
		sprintf(abs,"%s/%s",cwd,path);
	}

	//now create the final path without useless . .. and /
	if(!resolved_path)resolved_path = malloc(strlen(abs)+1);
	if(!resolved_path)goto end;

	char *dest = resolved_path;
	char *src  = abs;
	char last  = '\0';
	while(*src){
		if(*src == '/'){
			// "/./" are useless
			if(!strncmp(src,"/./",3) || !strcmp(src,"/.")){
				//skip the "/." but keep the last /
				src+=2;
				continue;
			}

			//mutiples / next to each other is useless
			if(last != '/')last = *(dest++) = *src;

			// with "/../" we go back to parent
			if(!strncmp(src,"/../",4) || !strcmp(src,"/..")){
				//skip the "/.." but keep the last /
				src += 3;

				//if we have a / remove it
				//don't remove if it is the first / else edge case like /.. don't work
				if(dest > resolved_path + 1 && *(dest-1) == '/'){
					dest--;
				}

				//remove until start or /
				//NOTE : this work even on root because .. of root(nothing since we removed the /) is root(nothing)
				while(dest > resolved_path && *(dest-1) != '/')dest--;
				last = dest == resolved_path ? '\0' : *(dest-1);

				continue;
			}
			src++;
			continue;
		}
		last = *(dest++) = *(src++);
	}
	*dest = '\0';
end:
	free(abs);
	return resolved_path;
}
