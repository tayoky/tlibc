#ifndef _ABI_WAIT_H
#define _ABI_WAIT_H

// Stanix wait ABI

#include <features.h>

#define WNOHANG 0x01

#define __WCOREFLAG 0x80

#define WEXITSTATUS(x)  (((x) & 0xff00) >> 8)
#define WTERMSIG(x)     ((x) & 0x7f)
#define WSTOPSIG(x)     WEXITSTATUS(x)
#define WIFEXITED(x)    (WTERMSIG(x) == 0)
#define WIFSIGNALED(x)  (((signed char) (WTERMSIG(x) + 1) >> 1) > 0)
#define WIFSTOPPED(x)   (((x) & 0xff) == 0x7f)
#define WIFCONTINUED(x) ((x) == 0xffff)

#ifdef _DEFAULT_SOURCE
#define WCOREFLAG __WCOREFLAG
#endif

#if defined(_DEFAULT_SOURCE) || (defined(_POSIX_C_SOURCE) && _POSIX_C_SOURCE >= 202401)
#define WCOREDUMP(x) ((x) & __WCOREFLAG)
#endif

#ifdef _DEFAULT_SOURCE
#define W_EXITCODE(ret, sig) (((ret) << 8) | (sig))
#endif

#endif
