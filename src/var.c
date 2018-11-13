#include <nonamedef.h>

int syntax_hl = TRUE;

int was_edit = FALSE;

int command_mode = FALSE;


char* bottom_text;

int command_mode_key[3];
int command_mode_key_len;

void init_befor_var()
{
	bottom_text = MSOCHARARR;
	bottom_text[0] = '\0';
}

void init_var()
{
	syntax_hl = has_arg_syntax_file();
}
