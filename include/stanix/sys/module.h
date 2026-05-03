#ifndef _SYS_MODULE_H
#define _SYS_MODULE_H

int insmod(const char *pathname,const char **argv);
int rmmod(const char *name);

#endif