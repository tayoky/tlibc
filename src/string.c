#include <string.h>
#include <stdint.h>
#include <ctype.h>
#include <stdlib.h>

char *strcpy(char *dest, const char *src){
	size_t index = 0;
	while (src[index]){
		dest[index] = src[index];
		index++;
	}
	dest[index] = '\0';
	return dest;
}

char *strncpy(char *dest, const char *src,size_t n){
	size_t index = 0;
	while (src[index]){
		dest[index] = src[index];
		index++;
		if(index >= n){
			return dest;
		}
	}
	dest[index] = '\0';
	return dest;
}

size_t strlen(const char *str){
	size_t index = 0;
	while (str[index]){
		index ++;
	}
	return index;
}

char *strstr(const char *str1,const char *str2){
	size_t str2_len = strlen(str2) + 1;
	while(*str1){
		//check all char
		for(size_t i=0;i<str2_len;i++){
			if(!str2[i]){
				//all str2 was found
				return (char *)str1;
			}

			if(str1[i] != str2[i]){
				break;
			}
		}
		str1++;
	}
	return NULL;
}

void *memset(void *pointer,int value,size_t count){
	uint8_t *ptr = pointer;
	while (count > 0){
		*ptr = value;
		ptr++;
		count--;
	}
	
	return pointer;
}


int strcmp(const char *str1,const  char *str2){
	while (*str1 || *str2) {
		if (*str1 != *str2) return *str1 - *str2;
		str1++; str2++;
	}
	return 0;
}

int strncmp(const char *str1,const  char *str2,size_t n){
	while (*str1 || *str2) {
		if(n <= 0){
			return 0;
		}
		if (*str1 != *str2) return *str1 - *str2;
		n--;
		str1++; str2++;
	}
	return 0;
}

char *strchr(const char *str, int c){
	while(*str){
		if(*str == c){
			return (char *)str;
		}
		str++;
	}
	return NULL;
}

char *strrchr(const char *str, int c){
	//start with the right
	int i = strlen(str);
	while(i > 0){
		if(str[i] == c){
			return (char *)&str[i];
		}
		i--;
	}
	return NULL;
}

char *strpbrk(const char *str,const char *search){
	while(*str){
		for (size_t i = 0; i < strlen(search); i++){
			if(*str == search[i]){
				return (char *)str;
			}
		}
		str++;
	}
	return NULL;
}

char *strcat(char * dest, const char * src){
	while(*dest){
		dest++;
	}
	return strcpy(dest,src);
}

int strcasecmp(const char *str1, const char *str2){
	while (*str1 || *str2) {
		int c1 = tolower(*(unsigned char *)str1);
		int c2 = tolower(*(unsigned char *)str2);
		if (c1 != c2) return c1 - c2;
		str1++; str2++;
	}
	return 0;
}
int strncasecmp(const char *str1, const char *str2, size_t n){
	while (*str1 || *str2) {
		if(n <= 0){
			return 0;
		}
		int c1 = tolower(*(unsigned char *)str1);
		int c2 = tolower(*(unsigned char *)str2);
		if (c1 != c2) return c1 - c2;
		n--;
		str1++; str2++;
	}
	return 0;
}


void *memcpy(void *dest, const void *src,size_t n){
#ifdef x86_64
	asm("rep movsb"
		: : "D" (dest),
		    "S" (src),
		    "c" (n));
#else
	void *prev = dest;
	while(n > 0){
		*(char *)dest = *(char *)src;
		(char *)dest++;
		(char *)src++;
		n--;
	}
	dest = prev;
#endif
	return dest;
}

void *memmove(void *dest, const void *src, size_t n){
	if(dest == src){
		return dest;
	}

	if(dest < src){
		return memcpy(dest,src,n);
	}

#ifdef x86_64
	asm("rep movsq"
		: : "D" (dest),
		    "S" (src),
		    "c" (n));
#else
	while(n < 0){
		n--;
		((char *)dest)[n] = ((char *)src)[n];
	}
#endif
	return dest;
}

int memcmp(const void *buf1,const void *buf2,size_t count){
	while (count > 0){
		if(*(char *)buf1 != *(char *)buf2)return *(char *)buf1 - *(char *)buf2;
		(char *)buf1++;
		(char *)buf2++;
		count--;
	}

	return 0;
}

void *memchr(const void *buf, int c, size_t count){
	while(count){
		if(*(char *)buf == c){
			return (void *)buf;
		}
		buf++;
		count--;
	}
	return NULL;
}

char *strdup(const char *str){
	char *newstr = malloc(strlen(str) + 1);
	strcpy(newstr,str);
	return newstr;
}

char *strndup(const char *str,size_t count){
	size_t len = strlen(str);
	if(len >= count - 1){
		len = count -1;
	}

	char *newstr = malloc(len + 1);
	newstr[len] = '\0';
	return memcpy(newstr,str,len);
}
