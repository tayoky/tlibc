#include <unistd.h>
#include <fcntl.h>

// the stanix kernel provide a very usefull fdname syscall

char *ttyname(int fd) {
    return fdname(fd);
}

int ttyname_r(int fd, char *buf, size_t size) {
    return fdname_r(fd, buf, size);
}
