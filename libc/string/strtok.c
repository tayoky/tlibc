#include <string.h>

char *strtok(char *str, const char *delim){
    static char *ptr;
    return strtok_r(str,delim,&ptr);
}

char *strtok_r(char *str, const char *delim,char **saveptr){
    if(str){
        *saveptr = str;
        return NULL;
    }

    //skip delimiter until first char
    while(strchr(delim,**saveptr) && **saveptr)(*saveptr)++;
    char *ret = *saveptr;

    //now continute until delemiter
    while(!strchr(delim,**saveptr) && **saveptr)(*saveptr)++;

    if(!*ret)return NULL;
    return ret;
}