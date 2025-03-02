#ifndef STAT_H
#define STAT_H

#include <sys/type.h>
#include <sys/types.h>

struct stat {
	dev_t     st_dev;      //ID of device containing file
	ino_t     st_ino;      //file serial number
	mode_t    st_mode;     //mode of file (see below)
	nlink_t   st_nlink;    //number of links to the file
	uid_t     st_uid;      //user ID of file
	gid_t     st_gid;      //group ID of file
	dev_t     st_rdev;     //device ID (if file is character or block special)
	off_t     st_size;     //file size in bytes (if file is a regular file)
	time_t    st_atime;    //time of last access
	time_t    st_mtime;    //time of last data modification
	time_t    st_ctime;    //time of last status change
	blksize_t st_blksize;  //a filesystem-specific preferred I/O block size for
	blkcnt_t  st_blocks;   //number of blocks allocated for this object
};

#define S_IRUSR 0x04
#define S_IWUSR 0x02
#define S_IXUSR 0x01
#define S_IRWXU S_IRUSR | S_IWUSR | S_IXUSR
#define S_ISUID 0x08 //set uid bit

#define S_IRGRP 0x40
#define S_IWGRP 0x20
#define S_IXGRP 0x10
#define S_IRWXG S_IRGRP | S_IWGRP | S_IXGRP
#define S_ISGID 0x80 //set gid bit

#define S_IROTH 0x400
#define S_IWOTH 0x200
#define S_IXOTH 0x100
#define S_IRWXO S_IROTH | S_IWOTH | S_IXOTH
#define S_ISVTX 800 //restriction deletion bit

//files types
#define S_IFBLK 0x01000 //block device
#define S_IFCHR 0x02000 //character device
#define S_IFIFO 0x04000 //FIFO (Firt In First Out) 
#define S_IFREG 0x08000 //regular file
#define S_IFDIR 0x10000 //directory
#define S_IFLNK 0x20000 //symbolic link

//types test

#define S_ISBLK(m)  m & S_IFBLK //Test for a block special file. 
#define S_ISCHR(m)  m & S_IFCHR //Test for a character special file. 
#define S_ISDIR(m)  m & S_IFDIR //Test for a directory. 
#define S_ISFIFO(m) m & S_IFIFO //Test for a pipe or FIFO special file. 
#define S_ISREG(m)  m & S_IFREG //Test for a regular file. 
#define S_ISLNK(m)  m & S_IFLNK //Test for a symbolic link. 

//functions
int fstat(int fd,struct stat *st);
int stat(const char *pathname,struct stat *st);
int lstat(const char *pathname,struct stat *st);

#endif