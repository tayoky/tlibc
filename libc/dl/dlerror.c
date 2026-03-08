#include <dlfcn.h>

#ifndef __DYNAMIC__
char *dlerror(void){
    return "Executable is staticly linked";
}
#endif
