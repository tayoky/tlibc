#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <pwd.h>

static struct passwd _pwbuf;
static char _buf[1048];
static FILE *passwd_file = NULL;

#define OUT(c) if(size > 0){\
            *(unsigned char *)buf = c;\
            buf++;\
            size--;\
        } else {\
            return __set_errno(-ERANGE);\
        }
#define PARSE_STR(var,end) var = buf;\
    while((c = fgetc(stream) != end)){\
        if(c == EOF)return -1;\
        OUT(c);\
        c ++;\
    }\
    OUT('\0');
#define PARSE_INT(var,end) var = 0;\
    while((c = fgetc(stream) != ':')){\
        if(c == EOF)return -1;\
        var *= 10;\
        var += c - '0';\
    }

//NOT SAFE FOR NUMBER
int fgetpwent_r(FILE *stream, struct passwd *pwbuf,char *buf, size_t size,struct passwd **pwbufp){
    *pwbufp = NULL;
    int c = 0;
    PARSE_STR(pwbuf->pw_name,':');
    PARSE_STR(pwbuf->pw_passwd,':');
    PARSE_INT(pwbuf->pw_uid,':');
    PARSE_INT(pwbuf->pw_gid,':');
    PARSE_STR(pwbuf->pw_gecos,':');
    PARSE_STR(pwbuf->pw_dir  ,':');
    PARSE_STR(pwbuf->pw_shell,'\n');
    *pwbufp = pwbuf;
    return 0;
}

struct passwd *fgetpwent(FILE *stream){
    if(fgetpwent_r(stream,&_pwbuf,_buf,sizeof(_buf),NULL) < 0){
        return NULL;
    } else {
        return &_pwbuf;
    }
}

void setpwent(void){
    if(passwd_file){
        rewind(passwd_file);
    } else {
        passwd_file = fopen("/etc/passwd","r");
    }
}

int getpwent_r(struct passwd *pwbuf,char *buf, size_t size,struct passwd **pwbufp){
    if(!passwd_file){
        passwd_file = fopen("/etc/passwd","r");
        if(!passwd_file)return __set_errno(-EIO);
    }
    return fgetpwent_r(passwd_file,pwbuf,buf,size,pwbufp);
}

struct passwd *getpwent(void){
    if(!passwd_file){
        passwd_file = fopen("/etc/passwd","r");
        if(!passwd_file)return NULL;
    }
    return fgetpwent(passwd_file);
}

void endpwent(void){
    if(passwd_file){
        fclose(passwd_file);
        passwd_file = NULL;
    }
}

int getpwuid_r(uid_t uid, struct passwd *pwd, char *buffer,size_t bufsize, struct passwd **result){
    setpwent();
    for(;;){
        int ret;
        if((ret = getpwent_r(pwd,buffer,bufsize,result)) < 0){
            return ret;
        }
        if(pwd->pw_uid == uid){
            return 0;
        }
    }
    *result = NULL;
    return 0;
}

struct passwd *getpwuid(uid_t uid){
    struct passwd *ret;
    getpwuid_r(uid,&_pwbuf,_buf,sizeof(_buf),&ret);
    return ret;
}

int getpwnam_r(const char *name, struct passwd *pwd, char *buffer,size_t bufsize, struct passwd **result){
    setpwent();
    for(;;){
        int ret;
        if((ret = getpwent_r(pwd,buffer,bufsize,result)) < 0){
            return ret;
        }
        if(!strcmp(name,pwd->pw_name)){
            return 0;
        }
    }
    *result = NULL;
    return 0;
}

struct passwd *getpwnam(const char *name){
    struct passwd *ret;
    getpwnam_r(name,&_pwbuf,_buf,sizeof(_buf),&ret);
    return ret;
}
