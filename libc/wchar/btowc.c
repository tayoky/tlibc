#include <wchar.h>
#include <stdint.h>

//btowc for utf8
wint_t btowc(int c){
	if(c < 0){
		return WEOF;
	} else if(c <= 0x7f){
		return c;
	} else if(c <= 0x7ff){
		const uint8_t b1 = (1<<7) | (c & 0x3f);
		const uint8_t b2 = (3<<6) | ((c >> 6) & 0x1f);
		return (b2 << 8) | b1;
	} else {
		return WEOF;
	}
}
