#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>
#include <errno.h>

int tcgetattr(int fd,struct termios *termios_p){
	return ioctl(fd,TIOCGETA,termios_p);
}
int tcsetattr(int fd,int optional_actions,const struct termios *termios_p){
	switch(optional_actions){
	case TCSANOW:
		return ioctl(fd,TIOCSETA,(void *)termios_p);
	case TCSAFLUSH:
		return ioctl(fd,TIOCSETAF,(void *)termios_p);
	case TCSADRAIN:
		return ioctl(fd,TIOCSETAW,(void *)termios_p);
	default:
		return __set_errno(-EINVAL);
		break;
	}
}

pid_t tcgetprgp(int fd){
	pid_t pgrp;
	return ioctl(fd,TIOCGPGRP,&pgrp) < 0 ? -1 : pgrp;
}

int tcsetpgrp(int fd,pid_t pgrp){
	return ioctl(fd,TIOCSPGRP,&pgrp);
}

void cfmakeraw(struct termios *termios_p){
	termios_p->c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL | IXON);
	termios_p->c_oflag &= ~OPOST;
	termios_p->c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN);
}

int tcflush(int fd, int queue_selector){
	(void)fd;
	(void)queue_selector;
	//TODO : do we even need this ?
	return 0;
}

speed_t cfgetispeed(const struct termios *termios_p){
	return (termios_p->c_cflag >> IBSHIFT) & CBAUD;
}

speed_t cfgetospeed(const struct termios *termios_p){
	return termios_p->c_cflag & CBAUD;
}

int cfsetispeed(struct termios *termios_p, speed_t speed){
	termios_p->c_cflag &= ~CIBAUD;
	termios_p->c_iflag |= speed << IBSHIFT;
	return 0;
}

int cfsetospeed(struct termios *termios_p, speed_t speed){
	termios_p->c_cflag &= ~CBAUD;
	termios_p->c_iflag |= speed;
	return 0;
}

int cfsetspeed(struct termios *termios_p, speed_t speed){
	cfsetispeed(termios_p,speed);
	return cfsetospeed(termios_p,speed);
}
