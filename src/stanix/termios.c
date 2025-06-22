#include <sys/ioctl.h>
#include <termios.h>
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
