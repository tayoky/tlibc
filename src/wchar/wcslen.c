#include <wchar.h>

size_t wcslen(const wchar_t *ws){
	size_t size = 0;
	while(*ws){
		ws++;
		size++;
	}
	return size;
}
