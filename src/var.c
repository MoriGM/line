#include <nonamedef.h>

int syntax_hl = TRUE;

void init_var()
{
	syntax_hl = has_arg_syntax_file();
}
