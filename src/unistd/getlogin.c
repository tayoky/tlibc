#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pwd.h>

char *getlogin(void){
	static char buf[256];
	if(getlogin_r(buf,sizeof(buf)) < 0)return NULL;
	return buf;
}

int getlogin_r(char *buf, size_t bufsize){
	char *name = getenv("LOGNAME");
	if(!name) name = getenv("USER");
	if(!name) name = getenv("NAME");
	if(name){
		strncpy(buf,name,bufsize);
		return 0;
	}

	struct passwd *pwd = getpwuid(geteuid());
	if(!pwd)return -1;
	strncpy(buf,pwd->pw_name,bufsize);
	return 0;
}