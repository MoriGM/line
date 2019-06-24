#ifndef ARG_H
#define ARG_H

struct 
{
	int argc;
	char** argv;
} ARG_SYSTEM;

void init_arg(int argc, char** argv);
int has_arg(char* arg);
int has_arg_or_short_arg(char* short_arg,char* arg);
char** get_argv(void);
int get_argc(void);

#endif
