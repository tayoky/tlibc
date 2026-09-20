#ifndef _FEATURES_H
#define _FEATURES_H

#ifdef _TLIBC_SOURCE
#undef _GNU_SOURCE
#define _GNU_SOURCE 1
#endif

#ifdef _GNU_SOURCE
#undef _DEFAULT_SOURCE
#define _DEFAULT_SOURCE 1
#undef _XOPEN_SOURCE
#define _XOPEN_SOURCE 700
#undef _ATFILE_SOURCE
#define _ATFILE_SOURCE 1
#undef _LARGEFILE64_SOURCE
#define _LARGEFILE64_SOURCE 1
#endif

#ifdef _DEFAULT_SOURCE
#undef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200809L
#endif

#if defined(_POSIX_C_SOURCE) && _POSIX_C_SOURCE >= 1
#undef _POSIX_SOURCE
#define _POSIX_SOURCE 1
#endif

#endif
