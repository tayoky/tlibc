#include <setjmp.h>
#include <signal.h>


//helper for assembly sigsetjmp
void __sigsavemask(sigjmp_buf env, int savemask){
	env[0].savemask = savemask;
	if(savemask){
		sigprocmask(0,NULL,&env[0].mask);
	}
}

void siglongjmp(sigjmp_buf env, int val){
	if(env[0].savemask)sigprocmask(SIG_SETMASK,&env[0].mask,NULL);
	return longjmp(env[0].buf,val);
}
