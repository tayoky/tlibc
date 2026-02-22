#include <wchar.h>

wchar_t *fgetws(wchar_t *ws, int n, FILE *stream){
	wchar_t *ret = ws;
	//read until '\n'
	wint_t wc = 0;
	do {
		if(n <= 0){
			break;
		}
		wc = fgetwc(stream);

		//if EOF quit immediatlely
		if(wc == WEOF){
			break;
		}

		*ws = (wchar_t)wc;
		ws++;
		n--;
	} while (wc != L'\n');

	if(n >= 1)*ws = L'\0';
	return ret;
}
