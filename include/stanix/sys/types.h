#ifndef SYS_TYPES_H
#define SYS_TYPES_H

#ifdef i386
#define SYS_T int
#else
#define SYS_T long
#endif

typedef SYS_T pid_t;

typedef SYS_T uid_t;
typedef SYS_T gid_t;
typedef int mode_t;
typedef SYS_T nlink_t ;

typedef SYS_T time_t;
typedef unsigned SYS_T useconds_t;
typedef SYS_T suseconds_t;

//stupid bloat for posix API
typedef SYS_T dev_t;
typedef SYS_T ino_t;
typedef SYS_T blksize_t; //WTF don't exist and why a program will need that ???
typedef SYS_T blkcnt_t;

#ifdef i386
typedef unsigned int off_t;
typedef unsigned int size_t;
typedef signed   int ssize_t;
#else
typedef unsigned long long off_t;
typedef unsigned long long size_t;
typedef signed   long long ssize_t;
#endif
#endif