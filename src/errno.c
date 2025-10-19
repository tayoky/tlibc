#include <errno.h>

int *__errno_location(void){
    static int err;
    return &err;
}