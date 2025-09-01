#include <wchar.h>

wchar_t *wcspbrk(const wchar_t *wcs,const wchar_t *search){
	while(*wcs){
		for (size_t i = 0; i < wcslen(search); i++){
			if(*wcs == search[i]){
				return (wchar_t *)wcs;
			}
		}
		wcs++;
	}
	return NULL;
}
