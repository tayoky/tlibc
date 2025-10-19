#include <errno.h>
#include <tlibc.h>

int *__errno_location(void){
#ifdef LIBK
    static int stub;
    return &stub;
#else
    return &__get_uthread()->err;
#endif
}