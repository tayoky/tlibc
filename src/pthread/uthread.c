#include <sys/mman.h>
#include <tlibc.h>
#include <limits.h>
#include <stddef.h>

#define UTHREAD_SIZE ((sizeof(struct __uthread) + PAGE_SIZE - 1) / PAGE_SIZE)

struct __uthread *__new_uthread(void){
    struct __uthread *uthread = mmap(NULL,UTHREAD_SIZE,PROT_READ | PROT_WRITE,MAP_PRIVATE | MAP_ANONYMOUS,0,0);
    if(uthread == MAP_FAILED){
        return NULL;
    }

    uthread->self = uthread;

    return uthread;
}

void __free_uthread(struct __uthread *uthread){
    munmap(uthread,UTHREAD_SIZE);
}