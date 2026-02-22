#include <time.h>

char *asctime(const struct tm *timeptr){
	static char buf[256];
	return asctime_r(timeptr,buf);
}
