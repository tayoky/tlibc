#include <tlibc.h>
#include <stddef.h>

char *fake_envp[] = {
	"PATH=initrd:/bin;initrd:/",
	NULL,
};

void __init_tlibc(int argc,char **argv,int envc,char **envp){
	__init_heap();

	//when writing this stanix don't support environement variable
	//so emulate one
	
	envc = 1;
	__init_environ(argc,argv,envc,fake_envp);
}