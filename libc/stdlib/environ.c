#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <errno.h>
#include <stdio.h>
#include <tlibc.h>

//environement variable manipulation
__attribute__((weak)) char **environ;

#ifdef __DL_TLIBC__

// for the dynamic linker, don't allocate memory
void __init_environ(char **envp) {
	environ = envp;
}

#else

void __init_environ(char **envp) {
	//envp is created by the kernel
	//so we can't realloc it
	//copy it to normal memory

	int envc = 0;
	while (envp[envc]) envc++;

	environ = malloc((envc + 1) * sizeof(char *));
	for (int i = 0; envp[i]; i++) {
		environ[i] = envp[i];
	}
	//last NULL entry
	environ[envc] = NULL;
}
#endif
