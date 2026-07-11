#ifndef _TERMIOS_H
#define _TERMIOS_H

#include <abi/termios.h>
#include <sys/types.h>

#define TCIOFLUSH 0
#define TCIFLUSH  1
#define TCOFLUSH  2

int tcgetattr(int fd,struct termios *termios_p);
int tcsetattr(int fd,int optional_actions,const struct termios *termios_p);
pid_t tcgetprgp(int fd);
int tcsetpgrp(int fd,pid_t pgrp);
void cfmakeraw(struct termios *termios_p);
int tcflush(int fd, int queue_selector);
speed_t cfgetispeed(const struct termios *termios_p);
speed_t cfgetospeed(const struct termios *termios_p);
int cfsetispeed(struct termios *termios_p, speed_t speed);
int cfsetospeed(struct termios *termios_p, speed_t speed);
int cfsetspeed(struct termios *termios_p, speed_t speed);

#endif
