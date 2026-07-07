#include <wchar.h>

int wcscoll(const wchar_t *ws1, const wchar_t *ws2) {
	// TODO : locale stuff
	return wcscmp(ws1, ws2);
}
