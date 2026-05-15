#include <sys/auxv.h>
#include <elf.h>
#include <errno.h>
#include <stdlib.h>

#ifdef __i386__
#define Elf_Auxv Elf32_Auxv
#else
#define Elf_Auxv Elf64_Auxv
#endif

extern char **environ;

unsigned long getauxval(unsigned long type) {
	long *auxv = (long *)environ;

	// jump over envp
	while (*auxv) auxv++;
	auxv++;

	Elf_Auxv *entry = (Elf_Auxv *)auxv;
	while (entry->a_type != AT_NULL) {
		if (entry->a_type == (long)type) {
			return entry->a_un.a_val;
		}
		entry++;
	}
	errno = ENOENT;
	return 0;
}
