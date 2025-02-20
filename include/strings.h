#ifndef STRINGS_H
#define STRINGS_H

#include <string.h>

#define strcasecmp  stricmp
#define strncasecmp strnicmp

#define bcmp memcmp
//TODO replace this with memmove
#define bcopy(src,dest,size) (void)memcpy(dest,src,size)

#define bzero(mem,size) (void)memset(mem,0,size)

#endif