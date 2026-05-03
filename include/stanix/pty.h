#ifndef _PTY_H
#define _PTY_H

#include <termios.h>
#include <sys/ioctl.h>

int openpty(int *amaster, int *aslave, char *name,const struct termios *termp,const struct winsize *winp);

#endif