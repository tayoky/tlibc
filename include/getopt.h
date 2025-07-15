#ifndef _GETOPT_H
#define _GETOPT_H

struct option {
	const char *name;
	int has_arg;
	int *flag;
	int val;
};

int getopt_long(int argc,char *const*argv,const char *optstring,const struct option *longopts, int *longindex);

extern int optind;
extern int opterr;
extern char *optarg;

#endif
