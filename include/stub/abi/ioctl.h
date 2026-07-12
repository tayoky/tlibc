#ifndef _ABI_IOCTL_H
#define _ABI_IOCTL_H

// Stub ioctl ABI

struct winsize {
	unsigned short	ws_row;	   //rows, in characters
	unsigned short	ws_col;	   //columns, in characters
	unsigned short	ws_xpixel; //horizontal size, pixels
	unsigned short	ws_ypixel; //vertical size, pixels
};

#endif
