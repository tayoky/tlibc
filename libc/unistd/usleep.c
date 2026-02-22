#include <unistd.h>
#include <time.h>

int usleep(useconds_t usec){
	struct timespec ts = {
		.tv_sec = usec / 1000000,
		.tv_nsec = (usec / 1000) % 1000,
	};
	return nanosleep(&ts,NULL);
}
