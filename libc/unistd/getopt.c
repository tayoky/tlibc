#include <getopt.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include <stdio.h>

int optind = 1;
int opterr = 1;
char *optarg = NULL;
int optopt;

int getopt(int argc,char *const*argv,const char *optstring){
	return getopt_long(argc,argv,optstring,NULL,NULL);
}

int getopt_long(int argc,char *const*argv,const char *optstring,const struct option *longopts, int *longindex){
	if(optind == 0)optind = 1;
	int non_option_handling = 0;
	int aerror = 0;
	if(optstring[0] == '+' || getenv("POSIXLY_CORRECT")){
		if(optstring[0] == '+')optstring++;
		non_option_handling = -1;
	} else if(optstring[0] == '-'){
		optstring++;
		non_option_handling = 1;
	}
	if(optstring[0] == ':'){
		optstring++;
		aerror = 1;
	}

	if(optind >= argc){
		return -1;
	}

	char d[strlen(argv[0])-1];
	strcpy(d,argv[0]);
	char *prog_name = basename(d);

	//check it's an option
	if(argv[optind][0] != '-'){
		switch(non_option_handling){
		case -1:
			optarg = argv[optind];
			optind++;
			return 1;
		case 1:
			return -1;
		case 0:
			//TODO:search an option and shift
			return -1;
		}
	}

	
	if(argv[optind][1] == '-'){
		//long option
		
		//the arg "--" should stop the option parsing
		if(argv[optind][2] == '\0'){
			optind++;
			return -1;
		}

		if(longopts){
			for(int i=0; longopts[i].name; i++){
				//check for arg
				optarg = strchr(argv[optind],'=');
				if(optarg){
					*optarg = '\0';
					optarg++;
				}
				if(!strcmp(argv[optind] + 2,longopts[i].name)){
					if(longindex)*longindex = i;
					optind++;
					if(longopts[i].has_arg > 1 && !optarg){
						if(longopts[i].has_arg == 1 && optind >= argc){
							if(opterr && !aerror)fprintf(stderr,"%s: missing operand\n",prog_name);
							return aerror ? ':' : '?';
						}
						optarg = argv[optind];
						optind++;
					}
					if(longopts[i].has_arg == 0 && optarg){
						if(opterr && !aerror)fprintf(stderr,"%s: unexpected operand\n",prog_name);
						return '?';
					}
					if(longopts[i].flag){
						*longopts[i].flag = longopts[i].val;
						return 0;
					} else {
						return longopts[i].val;
					}
				}
			}
		}
		if(opterr && !aerror)fprintf(stderr,"%s: invalid option %s\n",prog_name,argv[optind]);
		optind++;
		return '?';
	}


	static int i = 1;
	int ret;
	char *c;
	if((c = strchr(optstring,argv[optind][i]))){
		ret = argv[optind][i];
		if(c[1] == ':'){
			//we need an argument
			if(c[2] == ':'){
				//it's optional
				optarg = &argv[optind][i+1];
				if(!*optarg)optarg = NULL;
				//skip th rest of the arg
				i = strlen(argv[optind])-1;
			} else {
				if(optind + 1 >= argc){
					if(aerror){
						ret = ':';
					} else {
						if(opterr)fprintf(stderr,"%s: missing operand\n",prog_name);
						ret = '?';
					}
				} else {
					optarg = argv[optind+1];
				}
			}
		}
	} else {
		if(opterr && !aerror){
			fprintf(stderr,"%s: invalid option -- %c\n",prog_name,argv[optind][7]);
		}
		ret = '?';
	}
	i++;
	if(!argv[optind][i]){
		i = 1;
		optind++;
	}

	return ret;
}
