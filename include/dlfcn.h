#ifndef _DLFCN_H
#define _DLFCN_H

void *dlopen(const char *path, int flags);
int dlclose(void *handle);
char *dlerror(void);
void *dlsym(void *handle, const char *sym);

#define RTLD_LAZY   0x01
#define RTLD_NOW    0x02
#define RTLD_GLOBAL 0x04
#define RTLD_LOCAL  0x08
#define RTLD_NOLOAD 0x10

#define RTLD_DEFAULT  (void*)0x1432
#define RTLD_NEXT     (void*)0x1234 

#endif
