#include <tlibc.h>
#include <stdlib.h>

extern int main(int argc,char **argv);

void _start(int argc,char **argv,int envc,char **envp){
	__init_tlibc(argc,argv,envc,envp);
	exit(main(argc,argv));
}
