#include <wchar.h>

wchar_t *wcschr(const wchar_t *ws, wchar_t wc) {
	while (*ws) {
		if (*ws == wc) return (wchar_t *)ws;
		ws++;
	}
	if (wc == 0) return ws;
	return NULL;
}
