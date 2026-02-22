#include <dlfcn.h>

char *dlerror(void){
    return "Executable is staticly linked";
}
