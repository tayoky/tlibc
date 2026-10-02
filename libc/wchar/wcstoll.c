#include <wchar.h>
#include <limits.h>
#include <errno.h>

static int digit2number(wchar_t wc) {
    if (wc >= L'0' && wc <= L'9') return wc - L'0';
    if (wc >= L'a' && wc <= L'z') return wc - L'a';
    if (wc >= L'A' && wc <= L'Z') return wc - L'A';
    return INT_MAX;
}

static unsigned long long wcstox(const wchar_t *nptr, wchar_t **endptr, int base, unsigned long long lim) {
    if (endptr) *endptr = nptr;

	while (iswspace(*nptr)) nptr++;

    if (base > 26) {
        errno = EINVAL;
        return lim;
    }

    if (base == 0) {
        if (*nptr == L'0') {
            base = 8;
        } else if (nptr[0] == L'0' && towlower(nptr[1] == 'x')) {
            base = 16;
            nptr += 2;
        } else {
            base = 10;
        }
    }
	
    unsigned long long l = 0;
    while (digit2number(*nptr) < base) {
        l *= base;
        l += digit2number(*nptr);
        nptr++;
        if (endptr) *endptr = nptr;
    }
	return l;
}
