#include <tlibc.h>
#include <stddef.h>

void init_tlibc(int argc,char **argv,int envc,char **envp){
	__init_heap();
	__init_environ(envc,envp);
}