#include <wchar.h>

int wcscmp(const wchar_t *ws1,const wchar_t *ws2){
	while(*ws1 || *ws2){
		if(*ws1 != *ws2)return *ws1 > *ws2 ? 1 : -1;
		ws1++;
		ws2++;
	}
	return 0;
}
