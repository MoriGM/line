#include "nonamedef.h"

void init_arg(int argc, char** argv)
{
	ARG_SYSTEM.argc = argc;
	ARG_SYSTEM.argv = argv;
}

int has_arg(char* arg)
{
	int i;
	for (i = 1;i < ARG_SYSTEM.argc;i++)
		if(!strcmp(arg, get_argv()[i]))
			return i;
	return 0;
}

int has_arg_or_short_arg(char* short_arg,char* arg)
{
	int i;
	for (i = 1;i < ARG_SYSTEM.argc;i++)
		if (!strcmp(arg, get_argv()[i]) || !strcmp(short_arg, get_argv()[i]))
			return i;
	return 0;
}

char** get_argv()
{
	return ARG_SYSTEM.argv;
}

int get_argc()
{
	return ARG_SYSTEM.argc;
}
