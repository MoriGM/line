#include <nonamedef.h>

int syntax_hl = TRUE;

int was_edit = FALSE;

int command_mode = FALSE;


char* bottom_text;

int command_mode_key[4];
int command_mode_key_len;

enum KEY_TYPE key_type = EDITOR; 

void init_befor_var()
{
	bottom_text = MSOCHARARR;
	bottom_text[3] = '\0';
}

void uninit_befor_var(void)
{
	mem_free_char_array(bottom_text);
}

void init_var()
{
	syntax_hl = has_arg_syntax_file();
}

void set_was_edit(int i)
{
	was_edit = i;
}
