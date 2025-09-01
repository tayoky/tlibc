#include <wchar.h>
#include <errno.h>
#include <stdint.h>

//wcrtomb for utf8
int wcrtomb(char *s,wchar_t wc,mbstate_t *ps){
	if(ps)ps = 0;

	int len = 0;
	if(wc <= 0x7f){
		len = 1;
	} else if(wc <= 0x7ff){
		len = 2;
	} else if(wc <= 0xffff){
		len = 3;
	} else if(wc <= 0x10ffff){
		len = 4;
	} else {
		return __set_errno(-EILSEQ);
	}

	if(!s)return len;

	if(len == 1){
		s[0] = 0x7f & (char)wc;
		return 0;
	}

	//higger bits of wc
	s[0] = (wc >> (8 * (len - 1))) & ~(1 << (8 - len - 1));
	//len indicator
	s[0] |= (char)(0xf00 >> len);

	for(int i=1; i<len; i++){
		int shift_amount = (len - i - 1);
		s[i] = 0x80 | (0xc0 & (uint8_t)(wc >> shift_amount));
	}

	return len;
}
