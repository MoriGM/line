#include <nonamedef.h>

extern int command_mode;
extern int was_edit;

int key_editor_left(int key)
{
	if (key == KEY_LEFT && MAIN_FRAME.pos_x >= 1)
	{
		POSX = POSX - 1;
		update_move_window();
		return 1;
	}
	else if (key == KEY_LEFT && POSX == 0 && POSC >= 1)
	{
		POSC = POSC - 1;
		draw_window();
		move(POSY, 0);
		return 1;
	}

	return 0;
}

int key_editor_enter(int key)
{
	if (key == KEY_ENTER || key == '\n')
	{
		was_edit = TRUE;
		add_line_monitor(0);
		draw_window();
		return 1;
	}
	return 0;
}

int key_editor_up(int key)
{
	if (key == KEY_UP && MAIN_FRAME.pos_y >= 1)
	{
		MAIN_FRAME.pos_y = MAIN_FRAME.pos_y - 1;
		if (MAIN_FRAME.pos_x > strlen(MAIN_FRAME.lines[MAIN_FRAME.pos_y]))
			MAIN_FRAME.pos_x = strlen(MAIN_FRAME.lines[MAIN_FRAME.pos_y]); 
		update_move_window();
		return 1;
	}
	else if (key == KEY_UP && MAIN_FRAME.pos_y == 0 && MAIN_FRAME.pos_line >= 1)
	{
		MAIN_FRAME.pos_line = MAIN_FRAME.pos_line - 1;
		draw_window();
		return 1;
	}
	return 0;
}

int key_editor_down(int key)
{
	if (key == KEY_DOWN && (size_y() - 1) > POSY && (MAIN_FRAME.line_count - 1) > read_y())
	{
		MAIN_FRAME.pos_y = MAIN_FRAME.pos_y + 1;
		if (MAIN_FRAME.pos_x > strlen(MAIN_FRAME.lines[read_y()]))
			MAIN_FRAME.pos_x = strlen(MAIN_FRAME.lines[read_y()]);
		update_move_window();
		return 1;
	}
	else if (key == KEY_DOWN && POSY >= (size_y() - 2) && MAIN_FRAME.line_count > (POSY + MAIN_FRAME.pos_line))
	{
		POSL = POSL + 1;
		draw_window();
		return 1;
	}
	return 0;
}

int key_editor_right(int key)
{
	if (key == KEY_RIGHT && POSX < size_x() && MAIN_FRAME.pos_x < strlen(MAIN_FRAME.lines[read_y()]))
	{	
		MAIN_FRAME.pos_x = MAIN_FRAME.pos_x + 1;
		update_move_window();
		return 1;
	}
	else if (key == KEY_RIGHT && POSX == size_x() && (POSC + size_x()) <= strlen(MAIN_FRAME.lines[read_y()]))
	{
		POSC = POSC + 1;
		draw_window();
		move(POSY, size_x() - 1);
		return 1;
	}
	return 0;
}
	

int key_editor_command_mode(int key)
{
	if (key == STRG('x'))
	{
		command_mode = TRUE;
		draw_window();
		return 1;
	}
	return 0;
}

int key_editor_quit(int key)
{
	if (key == STRG('d'))
	{
		sys_quit();
		return 1;
	}
	return 0;
}

int key_editor_backspace(int key)
{
	if(key == KEY_BACKSPACE)
	{
		was_edit = TRUE;
		remove_for_char_monitor();
		draw_window();
		return 1;
	}
	return 0;
}

int key_command_mode_save(int key[], int len)
{
	if (len == 1 && key[0] == 's')
	{
		save_window_file();
		return 1;
	}
	return 0;
}

int key_command_mode_quit(int key[], int len)
{
	if (len == 1 && key[0] == 'q')
	{
		if (!was_edit)
			sys_quit();
		return 1;
	}
	return 0;
}

int key_command_mode_console(int key[], int len)
{
	if (len == 1 && key[0] == 'c')
	{
		sys_console_open();
		return 1;
	}
	return 0;
}
