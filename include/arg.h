#ifndef ARG_H
#define ARG_H

struct arg_struct{
	int argc;
	char** argv;
};

extern struct arg_struct ARG_SYSTEM;

void init_arg(int argc, char** argv);
int has_arg(char* arg);
int has_arg_or_short_arg(char* short_arg,char* arg);
char** get_argv(void);
int get_argc(void);

#endif
