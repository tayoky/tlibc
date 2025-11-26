#ifndef _SYS_SHUDOWN_H
#define _SYS_SHUDOWN_H

int stanix_shutdown(int flags);

#define SHUTDOWN_FAST   0x01
#define SHUTDOWN_REBOOT 0x02

#endif
