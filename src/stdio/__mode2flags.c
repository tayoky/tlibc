#include <fcntl.h>

int __mode2flags(const char *mode){
	int flags = 0;
	//we don't care about binary or text mode
	
	if(mode[1] == '+' || (mode[1] && mode[2] == '+')){
		//both read an write
		flags |= O_RDWR;
	}

	switch (mode[0])
	{
	case 'r':
		break;
	case 'w':
		flags |= O_TRUNC;
		flags |= O_CREAT;
		if(!(flags & O_RDWR)){
			flags |= O_WRONLY;
		}
		break;
	case 'a':
		flags |= O_APPEND;
		flags |= O_CREAT;
		if(!(flags & O_RDWR)){
			flags |= O_WRONLY;
		}
		break;
	default:
		return -1;
		break;
	}

	return flags;
}
