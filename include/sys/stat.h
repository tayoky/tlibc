#ifndef _SYS_STAT_H
#define _SYS_STAT_H

#include <abi/stat.h>
#include <sys/types.h>

#define S_IRUSR 0400
#define S_IWUSR 0200
#define S_IXUSR 0100
#define S_IRWXU S_IRUSR | S_IWUSR | S_IXUSR

#define S_IRGRP 040
#define S_IWGRP 020
#define S_IXGRP 010
#define S_IRWXG S_IRGRP | S_IWGRP | S_IXGRP

#define S_IROTH 04
#define S_IWOTH 02
#define S_IXOTH 01
#define S_IRWXO S_IROTH | S_IWOTH | S_IXOTH

#define S_ISUID 04000 // set uid bit
#define S_ISGID 02000 // set gid bit
#define S_ISVTX 01000 // restriction deletion bit

// files types
#define S_IFMT   0170000
#define S_IFSOCK 0140000 // socket
#define S_IFLNK  0120000 // symbolic link
#define S_IFREG  0100000 // regular file
#define S_IFBLK  0060000 // block device
#define S_IFDIR  0040000 // directory
#define S_IFCHR  0020000 // character device
#define S_IFIFO  0010000 // FIFO (Firt In First Out) 

// types test

#define S_ISBLK(m)  ((m & S_IFMT) == S_IFBLK) //Test for a block special file. 
#define S_ISCHR(m)  ((m & S_IFMT) == S_IFCHR) //Test for a character special file. 
#define S_ISDIR(m)  ((m & S_IFMT) == S_IFDIR) //Test for a directory. 
#define S_ISFIFO(m) ((m & S_IFMT) == S_IFIFO) //Test for a pipe or FIFO special file. 
#define S_ISREG(m)  ((m & S_IFMT) == S_IFREG) //Test for a regular file. 
#define S_ISLNK(m)  ((m & S_IFMT) == S_IFLNK) //Test for a symbolic link. 
#define S_ISSOCK(m) ((m & S_IFMT) == S_IFSOCK) //Test for a socket. 


// functions
int stat(const char *pathname,struct stat *st);
int fstat(int fd,struct stat *st);
int lstat(const char *pathname,struct stat *st);
int fstatat(int fd, const char *restrict path, struct stat *restrict st, int flags);
int chmod(const char *pathname, mode_t mode);
int fchmod(int fd, mode_t mode);
int lchmod(const char *pathname,mode_t mode);
int chown(const char *pathname, uid_t owner, gid_t group);
int fchown(int fd, uid_t owner, gid_t group);
int lchown(const char *pathname, uid_t owner, gid_t group);
mode_t umask(mode_t mask);
int mkdir(const char *pathname, mode_t mode);

#endif
