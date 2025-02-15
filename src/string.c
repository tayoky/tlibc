#include <string.h>
#include <stdint.h>

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

void *memset(void *pointer,int value,uint64_t count){
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
		if (*str1 > *str2) return 1;
		if (*str2 > *str1) return -1;
		str1++; str2++;
	}
	return 0;
}

int strncmp(const char *str1,const  char *str2,size_t n){
	while (*str1 || *str2) {
		if(n <= 0){
			return 0;
		}
		if (*str1 > *str2) return 1;
		if (*str2 > *str1) return -1;
		n--;
		str1++; str2++;
	}
	return 0;
}

char *strrchr(const char *str, int c){
	while(*str){
		if(*str == c){
			return (char *)str;
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

void *memcpy(void *dest, const void *src,size_t n){
	while (n > 0){
		*(char *)dest = *(char *)src;
		(char *)src++;
		(char *)dest++;
		n--;
	}
	return dest;
}

int memcmp(const void *buf1,const void *buf2,size_t count){
	while (count > 0){
		if(*(char *)buf1 < *(char *)buf2)return -1;
		if(*(char *)buf1 > *(char *)buf2)return 1;
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