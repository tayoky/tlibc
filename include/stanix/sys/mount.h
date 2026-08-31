#ifndef _SYS_MOUNT_H
#define _SYS_MOUNT_H

#define MS_NOATIME 0x01
#define MS_NODEV   0x02
#define MS_NOEXEC  0x04
#define MS_NOSUID  0x08
#define MS_RDONLY  0x10
#define MS_AUTO    0x20
#define MS_MOVE    0x40

int mount(const char *source,const char *target,const char *filesystemtype,unsigned long mountflags,const void *data);

int umount2(const char *target, int flags);
int umount(const char *target);

#endif
