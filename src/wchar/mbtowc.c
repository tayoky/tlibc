#include <wchar.h>
#include <errno.h>

//simple mbtowc for utf8
#define S_CHECK(c) ((c & (3<<6)) == 1<<7)
int mbtowc(wchar_t *dest,const char *s,size_t n){
	const unsigned char *src = (const unsigned char *)s;
	if(!src||n==0)return 0;
	int len;
	if(n >= 1 && src[0] <= 0x7F){
		len = 1;
	} else if(n >= 2 && (src[0] & 0xE0) == 0xC0 && S_CHECK(src[1])){
		len = 2;
	} else if(n >= 3 && (src[0] & 0xF0) == 0xE0 && S_CHECK(src[1]) && S_CHECK(src[2])){
		len = 3;
	} else if(n >= 4 && (src[0] & 0xF8) == 0xF0 && S_CHECK(src[1]) && S_CHECK(src[2]) && S_CHECK(src[3])){
		len = 4;
	} else {
		errno = EILSEQ;
		return -1;
	}

	if(!dest)return len;

	int shift = 0;
	*dest = 0;
	for(int i=len-1; i>0; i--){
		*dest |= (src[i] & 0x3F) << shift;
		shift += 6;
	}

	*dest |= (src[0] & (0x7F >> (len-1))) << shift;
	return len;

}
