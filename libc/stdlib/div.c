#include <stdlib.h>

div_t div(int number, int denom) {
    return (div_t){
        .quot = number / denom,
        .rem  = number % denom,
    };
}
