#include <nonamedef.h>

int syntax_hl = TRUE;

int was_edit = FALSE;

int command_mode = FALSE;

void init_var()
{
	syntax_hl = has_arg_syntax_file();
}
