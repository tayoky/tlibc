#include <wchar.h>

wchar_t *wcsrchr(const wchar_t *ws, wchar_t wc) {
	wchar_t *best = NULL;
	while (*ws) {
		if (*ws == wc) best = (wchar_t *)ws;
		ws++;
	}
	if (wc == 0) return (wchar_t *)ws;
	return best;
}
