#ifndef _SYSLOG_H
#define _SYSLOG_H

#include <stdarg.h>

void openlog(const char *ident, int option, int facility);
void closelog(void);
void vsyslog(int priority, const char *format, va_list ap);

static inline void syslog(int priority, const char *format, ...) {
	va_list args;
	va_start(args, format);
	vsyslog(priority, format, args);
	va_end(args);
}

int setlogmask(int mask);

// use the same values as glibc and mlibc
#define LOG_PID    0x01
#define LOG_CONS   0x02
#define LOG_NDELAY 0x08
#define LOG_ODELAY 0x04
#define LOG_NOWAIT 0x10
#define LOG_PERROR 0x20

#define LOG_KERN (0<<3)
#define LOG_USER (1<<3)
#define LOG_MAIL (2<<3)
#define LOG_DAEMON (3<<3)
#define LOG_AUTH (4<<3)
#define LOG_SYSLOG (5<<3)
#define LOG_LPR (6<<3)
#define LOG_NEWS (7<<3)
#define LOG_UUCP (8<<3)
#define LOG_CRON (9<<3)
#define LOG_AUTHPRIV (10<<3)
#define LOG_FTP (11<<3)

#define LOG_EMERG 0
#define LOG_ALERT 1
#define LOG_CRIT 2
#define LOG_ERR 3
#define LOG_WARNING 4
#define LOG_NOTICE 5
#define LOG_INFO 6
#define LOG_DEBUG 7


#endif
