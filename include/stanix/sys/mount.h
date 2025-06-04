#ifndef _SYS_MOUNT_H
#define _SYS_MOUNT_H

int mount(const char *source,const char *target,const char *filesystemtype,unsigned long mountflags,const void *data);


int unmount(const char *dir, int flags);
int umount(const char *target);

#endif