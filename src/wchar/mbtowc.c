#include <wchar.h>


int mbtowc(wchar_t *dest,const char *s,size_t n){
	return mbrtowc(dest,s,n,NULL);
}
