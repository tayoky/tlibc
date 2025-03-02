#ifndef SYS_TYPES_H
#define SYS_TYPES_H

typedef long pid_t;

typedef long uid_t;
typedef long gid_t;
typedef int mode_t;
typedef long nlink_t ;

typedef unsigned long off_t;

typedef long time_t;
typedef unsigned long useconds_t;
typedef long suseconds_t;

//stupid bloat for posix API
typedef long dev_t;
typedef long ino_t;
typedef long blksize_t; //WTF don't exist and why a program will need that ???
typedef long blkcnt_t;

typedef unsigned long size_t;
typedef long ssize_t;

#endif