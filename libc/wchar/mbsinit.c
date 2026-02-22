#include <wchar.h>

int mbsinit(const mbstate_t *ps){
	if(!ps || !*ps){
		return 1;
	}
	return 0;
}
