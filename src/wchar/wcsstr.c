#include <wchar.h>

wchar_t *wcsstr(const wchar_t *ws1,const wchar_t *ws2){
	size_t ws2_len = wcslen(ws2) + 1;
	do{
		//check all char
		for(size_t i=0;i<ws2_len;i++){
			if(!ws2[i]){
				//all str2 was found
				return (wchar_t *)ws1;
			}

			if(ws1[i] != ws2[i]){
				break;
			}
		}
	}while(*(ws1++));
	return NULL;
}
