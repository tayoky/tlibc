#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

static char *get_str(char *tz,char **end){
	char *start = tz;
	int extended = 0;
	for(;;){
		switch(*tz){
		case '\0':
			return NULL;
		case '<':
			extended = 1;
			tz++;
			continue;
		case '>':
			extended = 0;
			tz++;
			continue;
		case '-':
		case '+':
			if(!extended)goto finish;
		}
		if(isdigit(*tz)){
			if(!extended)goto finish;
		}
		if(!isalpha(*tz)){
			return NULL;
		}

		tz++;
	}
finish:
	if(tz - start < 3)return NULL;
	*end = tz;
	return strndup(start,tz - start);
}

static long get_offset(char *tz,char **end,int *error){
	int sign = 1;
	switch(*tz){
	case '+':
		tz++;
		break;
	case '-':
		sign = -1;
		tz++;
		break;
	}

	long off = 0;
	char *e;

	for(long mul=3600; mul>=1; mul/=60){
		off += strtol(tz,&e,10) * mul;
		if(e == tz){
			*error = 1;
			return 0;
		}
		tz = e;
		if(*tz != ':'){
			*end = tz;
			return sign * off;
		}
	}
	*end = tz;
	return sign * off;
}
//TODO : parse timezone file
void tzset(void){
	char *tz = getenv("TZ");
	if(!tz){
fallback:
		free(tzname[0]);
		free(tzname[1]);
		tzname[0] = strdup("UTC");
		tzname[1] = strdup("UTC");
		timezone = 0;
		daylight = 0;
		return;
	}
	int error = 0;

	if(*tz == ',')tz++;
	char *std = get_str(tz,&tz);
	if(!std)goto fallback;
	long off = get_offset(tz,&tz,&error);
	if(error){
		free(std);
		goto fallback;
	}

	free(tzname[0]);
	free(tzname[1]);

	tzname[0] = std;
	tzname[1] = strdup(std);
	timezone = off;
	daylight = 0;
}
