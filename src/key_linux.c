#include <nonamedef.h>

struct KEY_MAP **key_maps;
int key_map_count;

struct COMMAND_KEY **cmd_keys;
int cmd_key_count;

void init_key(void)
{
	key_maps = malloc(sizeof(struct KEY_MAP) * 1000);
	key_map_count = 0;

	cmd_keys = malloc(sizeof(struct KEY_MAP) * 1000);
	cmd_key_count = 0;

	#ifdef DEBUG
	add_key(EDITOR, STRG('d'), &key_editor_quit);
	add_key(HEXSHOW, STRG('d'), &key_editor_quit);
	#endif

	add_key(EDITOR, KEY_LEFT, &key_editor_left);
	add_key(EDITOR, STRG('x'), &key_editor_command_mode);
	add_key(EDITOR, KEY_ENTER, &key_editor_enter);
	add_key(EDITOR, '\n', &key_editor_enter);
	add_key(EDITOR, KEY_UP, &key_editor_up);
	add_key(EDITOR, KEY_BACKSPACE, &key_editor_backspace);	
	add_key(EDITOR, KEY_DOWN, &key_editor_down);
	add_key(EDITOR, KEY_RIGHT, &key_editor_right);
	add_key(HEXSHOW, KEY_UP, &key_hexshow_up);
	add_key(HEXSHOW, KEY_DOWN, &key_hexshow_down);
	add_key(HEXSHOW, 'q', &key_hexshow_close);

	add_command_key(&key_command_mode_save, get_int_array('s', 0, 0));
	add_command_key(&key_command_mode_quit, get_int_array('q', 0, 0));
	add_command_key(&key_command_mode_console, get_int_array('c', 0, 0));
	add_command_key(&key_command_mode_top_new_line, get_int_array('O', 0, 0));
	add_command_key(&key_command_mode_bottom_new_line, get_int_array('o', 0, 0));
	add_command_key(&key_command_mode_delete_line, get_int_array('d', 'l', 0));
	add_command_key(&key_command_mode_line_start, get_int_array('l', 's', 0));
	add_command_key(&key_command_mode_line_end, get_int_array('l', 'e', 0));
	add_command_key(&key_command_mode_upper_case, get_int_array('l', 'u', 'c'));
	add_command_key(&key_command_mode_lower_case, get_int_array('l', 'l', 'c'));
	add_command_key(&key_command_mode_line_top, get_int_array('l', 't', 0));
	add_command_key(&key_command_mode_line_bottom, get_int_array('l', 'b', 0));
	add_command_key(&key_command_mode_delete_befor, get_int_array('d', 'b', 0));
	add_command_key(&key_command_mode_delete_after, get_int_array('d', 'a', 0));
	add_command_key(&key_command_mode_hex_show, get_int_array('h', 'e', 'x'));
	add_command_key(&key_command_mode_force_quit, get_int_array('Q', 0, 0));
}


void add_key(enum KEY_TYPE type,int key, void (*func)(void))
{
	struct KEY_MAP *km = malloc(sizeof(struct KEY_MAP));

	km->type = type;
	km->function = func;
	km->key = key;

	key_maps[key_map_count] = km;

	key_map_count++;
}

int on_key(enum KEY_TYPE t, int key)
{
	for (int i = 0;i < key_map_count;i++)
	{
		struct KEY_MAP *km = key_maps[i];
		if (km->type == t && km->key == key)
		{
			km->function();
			return 1;
		}
	}
	return 0;
}

void add_command_key(void(*func)(void), int *command)
{
	struct COMMAND_KEY *ck = malloc(sizeof(struct COMMAND_KEY));
	ck->function = func;
	ck->command = command;
	cmd_keys[cmd_key_count] = ck;
	cmd_key_count++;

}

int on_command_key(int key[], int len)
{
	for (int i = 0;i < cmd_key_count;i++)
	{
		struct COMMAND_KEY *ck = cmd_keys[i];
		if (cmp_int_arr(ck->command, key))
		{
			ck->function();
			return 1;
		}
	}
	return 0;
}

void key_listener(void)
{
	int c = getch();

	if (c == KEY_RESIZE)
		return draw_window();

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
			for (int clear = 0;clear < 3;clear++)
				command_mode_key[clear] = 0;
			command_mode_key_len = 0;
		}

		draw_window();

		return;
	}
	else
	{	
		if (on_key(key_type, c))
			return;
	}


	if (!is_banned_key(c) && key_type == EDITOR)
	{
		was_edit = TRUE;
		add_char_monitor((char) c);
		draw_window();
	}
}

int is_banned_key(int c)
{
	return c == KEY_DOWN || c == KEY_UP || c == KEY_LEFT || c == KEY_RIGHT || c == STRG('c') || c == STRG('d') || c == KEY_RESIZE || c == -1;
}
