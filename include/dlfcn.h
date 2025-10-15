#ifndef _DLFCN_H
#define _DLFCN_H

void *dlopen(const char *path, int flags);
int dlclose(void *handle);
char *dlerror(void);

#endif