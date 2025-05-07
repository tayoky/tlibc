#ifndef SYS_TERMIOS
#define SYS_TERMIOS

typedef char cc_t;
typedef int speed_t;
typedef unsigned int tcflag_t;

#define NCCS 12

#define VEOF   1  //end of file character
#define VEOL   2  //end of line character
#define VERASE 3  //erase character
#define VINTR  4  //interrupt character
#define VKILL  5  //kill line character
#define VMIN   6  //minimum number of characters for noncanonical read
#define VQUIT  7  //quit character
#define VSTART 8  //enable output character
#define VSTOP  9  //stop output character
#define VSUSP  10 //suspend character (send SIGSTOP)
#define VTIME  11 //timeout for noncanonical read (in deciseconds)

struct termios {
	tcflag_t c_iflag;    //input modes
	tcflag_t c_oflag;    //output modes
	tcflag_t c_cflag;    //control modes
	tcflag_t c_lflag;    //local modes
	cc_t     c_cc[NCCS]; //control chars
};


#define IGNBRK  1UL << 0
#define BRKINT  1UL << 1
#define IGNPAR  1UL << 2
#define PARMRK  1UL << 3
#define INPCK   1UL << 4
#define ISTRIP  1UL << 5
#define INLCR   1UL << 6
#define IGNCR   1UL << 7
#define ICRNL   1UL << 8
#define IUCLC   1UL << 9
#define IXON    1UL << 10
#define IXANY   1UL << 11
#define IXOFF   1UL << 12
#define IMAXBEL 1UL << 13


#define OPOST   1UL << 0
#define OLCUC   1UL << 1
#define ONLCR   1UL << 2
#define OCRNL   1UL << 3
#define ONOCR   1UL << 4
#define ONLRET  1UL << 5
#define OFILL   1UL << 6
#define OFDEL   1UL << 7

#define ISIG    1UL << 0
#define ICANON  1UL << 1
#define ECHO    1UL << 2
#define ECHOE   1UL << 3
#define ECHOK   1UL << 4
#define ECHONL  1UL << 5
#define ECHOCTL 1UL << 6
#define ECHOKE  1UL << 7
#define NOFLSH  1UL << 8
#define TOSTOP  1UL << 9
#define IEXTEN  1UL << 10

#define TCSANOW   0
#define TCSADRAIN 1
#define TCSAFLUSH 2

int tcgetattr(int fd,struct termios *termios_p);
int tcsetattr(int fd,int optional_actions,const struct termios *termios_p);
void cfmakeraw(struct termios *termios_p);

#endif