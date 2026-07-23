#include <dlfcn.h>
#include <libintl.h>

__attribute__((weak)) char *dlerror(void) {
#ifdef __SHARED__
	return dgettext("tlibc", "Dynamic linker is not loaded");
#else
	return dgettext("tlibc", "Executable is staticly linked");
#endif
}
