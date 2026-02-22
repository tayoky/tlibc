#include <sys/mman.h>
#include <unistd.h>
#include <limits.h>
#include <fcntl.h>
#include <stdio.h>

//more or less portable posix shm api

#define SHM_PATH "/dev/shm"

int shm_open(const char *name, int oflag, mode_t mode){
    char full_path[PATH_MAX];
    sprintf(full_path,SHM_PATH"%s",name);
    return open(full_path,oflag,mode);
}

int shm_unlink(const char *name){
    char full_path[PATH_MAX];
    sprintf(full_path,SHM_PATH"%s",name);
    return unlink(full_path);
}