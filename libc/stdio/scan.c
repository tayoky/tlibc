#include <ctype.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int (*xscanf_getc)(void *);
typedef void (*xscanf_unget)(int, void *);

#define LEN_NONE  0
#define LEN_HH    1
#define LEN_H     2
#define LEN_L     3
#define LEN_LL    4
#define LEN_J     5
#define LEN_Z     6
#define LEN_T     7
#define LEN_BIG_L 8
static int vxscanf(xscanf_getc getc, xscanf_unget unget, void *arg, const char *fmt, va_list args) {
	int n = 0;

	while (*fmt) {
		switch (*fmt) {
		case ' ':;
			// skip any spaces
			int s = getc(arg);
			while (isspace(s)) s = getc(arg);
			unget(s, arg);
			break;
		case '%':
			fmt++;

			// set start by readinf lenght
			size_t lenght = 0;
			while (isdigit(*(unsigned char *)fmt)) {
				lenght *= 10;
				lenght += *(unsigned char *)fmt - '0';
				fmt++;
			}

			// now read the width
			size_t width = 0;
			switch (*fmt) {
			case 'h':
				fmt++;
				if (*fmt == 'h') {
					fmt++;
					width = LEN_HH;
				} else {
					width = LEN_H;
				}
				break;
			case 'l':
				fmt++;
				if (*fmt == 'l') {
					fmt++;
					width = LEN_LL;
				} else {
					width = LEN_L;
				}
				break;
			case 'z':
				fmt++;
				width = LEN_Z;
				break;
			case 'j':
				fmt++;
				width = LEN_J;
				break;
			case 't':
				fmt++;
				width = LEN_T;
				break;
			case 'L':
				fmt++;
				width = LEN_BIG_L;
				break;
			default:
				width = LEN_NONE;
				break;
			}

			// now interpret
			switch (*fmt) {
			case 'c':
				// TODO : read wchar in %c and %s ???
				fmt++;
				if (!lenght) lenght = 1;
				unsigned char *cs = va_arg(args, unsigned char *);
				;
				for (; lenght > 0; lenght--) {
					int c = getc(arg);
					if (c < 0) return n;
					*cs = c;
					cs++;
				}
				n++;
				break;
			case 's':
				// HOLY SHIT this is unsafe
				fmt++;
				if (lenght == 0) lenght = SIZE_MAX;
				unsigned char *str = va_arg(args, unsigned char *);
				int c = getc(arg);
				while (!(isblank(c) || c == '\n' || c < 0) && lenght > 0) {
					*str = c;
					str++;
					lenght--;
					c = getc(arg);
				}
				unget(c, arg);
				*str = '\0';
				n++;
				break;
				int base;
				int sign;
			case 'i':
			// TODO : handle sign
			case 'u':
				base = 0;
				goto integer;
			case 'd':
				base = 10;
integer:
				sign = 1;
				if (!base) {
					int c = getc(arg);
					if (c == 0) {
						c = getc(arg);
						if (c == 'x') {
							base = 16;
						} else {
							unget(c, arg);
							base = 8;
						}
					} else {
						unget(c, arg);
						base = 10;
					}
				}
				if (lenght == 0) lenght = SIZE_MAX;
				uintmax_t integer = 0;
				int d = getc(arg);
				static char l[] = "0123456789abcdef";
				while (isxdigit(d) && lenght > 0) {
					d = tolower(d);
					if (strchr(l, d) - l >= base) break;
					integer *= base;
					integer += strchr(l, d) - l;
					lenght--;
					d = getc(arg);
				}
				unget(d, arg);
				switch (width) {
				case LEN_HH:
					*va_arg(args, char *) = (char)integer * sign;
					break;
				case LEN_H:
					*va_arg(args, short *) = (short)integer * sign;
					break;
				case LEN_NONE:
					*va_arg(args, int *) = (int)integer * sign;
					break;
				case LEN_L:
					*va_arg(args, long *) = (long)integer * sign;
					break;
				case LEN_LL:
				case LEN_BIG_L:
					*va_arg(args, long long *) = (long long)integer * sign;
					break;
				default:
					*va_arg(args, int *) = (int)integer * sign;
					break;
				}
				n++;
				break;
			case 'o':
				base = 8;
				goto integer;
			case 'p':
				if (width == sizeof(int)) width = sizeof(uintptr_t);
				// fallthrough
			case 'x':
			case 'X':
				base = 16;
				goto integer;
			case 'e':
			case 'f':
			case 'g':
			case 'a':
				d = getc(arg);
				double value = 0.0;
				double pow   = 1.0;
				sign = 1;
				if (d == '+') {
					d = getc(arg);
				} else if (d == '-') {
					d = getc(arg);
					sign = -1;
				}

				while (isdigit(d)) {
					value *= 10;
					value += d - '0';
					d = getc(arg);
				}
				if (d == '.') {
					d = getc(arg);
				}
				while (isdigit(d)) {
					pow *= 10;
					value *= 10;
					value += d - '0';
					d = getc(arg);
				}
				unget(d, arg);
				value /= pow;
				value *= sign;
				switch (width) {
				case LEN_NONE:
				default:
					*va_arg(args, float *) = value;
					break;
				case LEN_L:
					*va_arg(args, double *) = value;
					break;
				case LEN_LL:
				case LEN_BIG_L:
					*va_arg(args, long double *) = value;
					break;
				}
				break;
			default:
				// unknow, so fail ... i guess ???
				return n;
			}
			break;
		default:;
			// expect exact char
			int c = getc(arg);
			if (c != *(unsigned char *)fmt) {
				unget(c, arg);
				return n;
			}
			break;
		}
		fmt++;
	}

	return n;
}

static int buf_getc(void *arg) {
	const unsigned char **buf = arg;
	unsigned char c = **buf;
	if (!c) return EOF;
	(*buf)++;
	return c;
}

static void buf_ungetc(int c, void *arg) {
	const char **buf = arg;
	if (c != EOF) (*buf)--;
}

int vsscanf(const char *buf, const char *fmt, va_list args) {
	return vxscanf(buf_getc, buf_ungetc, &buf, fmt, args);
}

int sscanf(const char *buf, const char *fmt, ...) {
	va_list args;
	va_start(args, fmt);
	int ret = vsscanf(buf, fmt, args);
	va_end(args);
	return ret;
}

int vfscanf(FILE *stream, const char *fmt, va_list args) {
	return vxscanf((void *)fgetc, (void *)ungetc, stream, fmt, args);
}

int fscanf(FILE *stream, const char *fmt, ...) {
	va_list args;
	va_start(args, fmt);
	int ret = vfscanf(stream, fmt, args);
	va_end(args);
	return ret;
}
