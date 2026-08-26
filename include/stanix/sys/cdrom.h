#ifndef _SYS_CDROM_H
#define _SYS_CDROM_H

#include <sys/ioctl.h>

#define CDROM_EJECT           18000
#define CDROM_LOCK            18001
#define CDROM_UNLOCK          18002
#define CDROM_READ_TOC_HEADER 18003
#define CDROM_READ_TOC_ENTRY  18004

typedef struct cdrom_toc_header {
	size_t first_track;
	size_t last_track;
} cdrom_toc_header_t;

typedef struct cdrom_toc_entry {
	size_t track;
	off_t start;
	size_t size;
} cdrom_toc_entry_t;
#endif
