#ifndef _ABI_MMAN_H
#define _ABI_MMAN_H

// Linux memory manager ABI

#define PROT_READ  0x1 /* page can be read */
#define PROT_WRITE 0x2 /* page can be written */
#define PROT_EXEC  0x4 /* page can be executed */
#define PROT_NONE  0x0 /* page can not be accessed */

#define MAP_SHARED    0x01 /* modification are syncronise to the file/device */
#define MAP_PRIVATE   0x02 /* create a copy on write page */
#define MAP_FIXED     0x10 /* interpret addr exactly */
#define MAP_ANONYMOUS 0x20 /* don't use a file */

#endif
