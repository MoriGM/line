#include <nonamedef.h>

struct KEY_MAP **key_maps;
int key_map_count;

struct COMMAND_KEY **cmd_keys;
int cmd_key_count;

void init_key()
{
	key_maps = malloc(sizeof(struct KEY_MAP) * 1000);
	key_map_count = 0;

	cmd_keys = malloc(sizeof(struct KEY_MAP) * 1000);
	cmd_key_count = 0;

	add_key(EDITOR, &key_editor_left);
	add_key(EDITOR, &key_editor_command_mode);
	add_key(EDITOR, &key_editor_enter);
	add_key(EDITOR, &key_editor_up);
	add_key(EDITOR, &key_editor_backspace);	
	add_key(EDITOR, &key_editor_quit);
	add_key(EDITOR, &key_editor_down);
	add_key(EDITOR, &key_editor_right);

	add_command_key(&key_command_mode_save);
	add_command_key(&key_command_mode_quit);
	add_command_key(&key_command_mode_console);
	add_command_key(&key_command_mode_top_new_line);
	add_command_key(&key_command_mode_bottom_new_line);
	add_command_key(&key_command_mode_delete_line);
	add_command_key(&key_command_mode_line_start);
	add_command_key(&key_command_mode_line_end);
	add_command_key(&key_command_mode_upper_case);
	add_command_key(&key_command_mode_lower_case);
	add_command_key(&key_command_mode_line_top);
	add_command_key(&key_command_mode_line_bottom);
}


void add_key(enum KEY_TYPE type, int (*func)(int))
{
	struct KEY_MAP *km = malloc(sizeof(struct KEY_MAP));

	km->type = type;
	km->function = func;

	key_maps[key_map_count] = km;

	key_map_count++;
}

int on_key(enum KEY_TYPE t, int key)
{
	for (int i = 0;i < key_map_count;i++)
	{
		struct KEY_MAP *km = key_maps[i];
		if (km->type == t)
			if (km->function(key))
				return 1;
	}
	return 0;
}

void add_command_key(int(*func)(int[], int))
{
	struct COMMAND_KEY *ck = malloc(sizeof(struct COMMAND_KEY));
	ck->function = func;
	cmd_keys[cmd_key_count] = ck;
	cmd_key_count++;

}

int on_command_key(int key[], int len)
{
	for (int i = 0;i < cmd_key_count;i++)
	{
		struct COMMAND_KEY *ck = cmd_keys[i];
		if (ck->function(key, len))
			return 1;
	}
	return 0;
}

void key_listener()
{
	int c = getch();

	extern int was_edit;
	extern int command_mode;
	extern int command_mode_key[];
	extern int command_mode_key_len;

	if (command_mode && !is_banned_key(c))
	{
		command_mode_key[command_mode_key_len] = c;
		command_mode_key_len = command_mode_key_len + 1;

		int flag = on_command_key(command_mode_key, command_mode_key_len) || command_mode_key_len == 3;

		if (flag)
		{
			command_mode = FALSE;
			command_mode_key_len = 0;
		}

		draw_window();

		return;
	}
	else
	{	
		if (on_key(EDITOR, c))
			return;
	}


	if (!is_banned_key(c))
	{
		was_edit = TRUE;
		add_char_monitor(c); 
		draw_window();
	}
}

int is_banned_key(int c)
{
	return c == KEY_DOWN || c == KEY_UP || c == KEY_LEFT || c == KEY_RIGHT || c == STRG('c') || c == STRG('s');
}
