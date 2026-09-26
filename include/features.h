#ifndef _FEATURES_H
#define _FEATURES_H

// see if we can use fast inline functions
#if defined(__OPTIMIZE__) && !defined(__NO_INLINE__) && !defined(TLIBC_NO_FAST_INLINES)
#undef  TLIBC_FAST_INLINES
#define TLIBC_FAST_INLINES 1
#endif


// deprecated
#if (defined( _BSD_SOURCE) || defined(_SVID_SOURCE)) && !defined(_DEFAULT_SOURCE)
# warning "_BSD_SOURCE and _SVID_SOURCE are deprecated, use _DEFAULT_SOURCE"
# undef  _DEFAULT_SOURCE
# define _DEFAULT_SOURCE 1
#endif

#ifdef _TLIBC_SOURCE
#undef  _GNU_SOURCE
#define _GNU_SOURCE 1
#endif

#ifdef _GNU_SOURCE
#undef  _ISOC95_SOURCE
#define _ISOC95_SOURCE 1
#undef  _ISOC99_SOURCE
#define _ISOC99_SOURCE 1
#undef  _ISOC11_SOURCE
#define _ISOC11_SOURCE 1
#undef  _ISOC2X_SOURCE
#define _ISOC2X_SOURCE 1
#undef  _DEFAULT_SOURCE
#define _DEFAULT_SOURCE 1
#undef  _XOPEN_SOURCE
#define _XOPEN_SOURCE 700
#undef  _XOPEN_SOURCE_EXTENDED
#define _XOPEN_SOURCE_EXTENDED	1
#undef  _ATFILE_SOURCE
#define _ATFILE_SOURCE 1
#undef  _LARGEFILE64_SOURCE
#define _LARGEFILE64_SOURCE 1
#endif

// by default turn the default source on
#if !defined(_DEFAULT_SOURCE) && !defined(__STRICT_ANSI__) && \
    !defined(_ISOC99_SOURCE) && !defined(_ISOC11_SOURCE) && \
    !defined(_ISOC2X_SOURCE) && !defined(_XOPEN_SOURCE) && \
    !defined(_POSIX_SOURCE) && !defined(_POSIX_C_SOURCE)
#undef  _DEFAULT_SOURCE
#define _DEFAULT_SOURCE	1
#endif

#if defined(_POSIX_C_SOURCE) && _POSIX_C_SOURCE >= 1
#undef  _POSIX_SOURCE
#define _POSIX_SOURCE 1
#elif defined(_POSIX_SOURCE) && _POSIX_SOURCE
#undef  _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 1
#elif defined(_DEFAULT_SOURCE)
#undef  _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200809L
#undef  _POSIX_SOURCE
#define _POSIX_SOURCE 1
#endif

// trigger the ISO C for POSIX source above 2001
#if defined(_POSIX_C_SOURCE) && _POSIX_C_SOURCE >= 200112L
#undef  _ISOC95_SOURCE
#define _ISOC95_SOURCE 1
#undef  _ISOC99_SOURCE
#define _ISOC99_SOURCE 1
#endif

// trigger _ATFILE_SOURCE for POSIX source above 2008
#if defined(_POSIX_C_SOURCE) && (_POSIX_C_SOURCE - 0) >= 200809L
#undef  _ATFILE_SOURCE
#define _ATFILE_SOURCE	1
#endif

#endif
