#include <wchar.h>

int wmemcmp(const wchar_t *ws1,const wchar_t *ws2,size_t n){
	while(n > 0){
		if(*ws1 != *ws2)return *ws1 > *ws2 ? 1 : -1;
		n--;
		ws1++;
		ws2++;
	}
	return 0;
}
