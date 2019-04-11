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
		
		set_was_edit(1);
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
		if ((POSX + POSC) > strlen(MAIN_FRAME.lines[read_y()]))
		{
			POSX = strlen(MAIN_FRAME.lines[read_y()]) % calc_max_x();
			POSC = strlen(MAIN_FRAME.lines[read_y()]) - POSX;
		}
		update_move_window();
		return 1;
	}
	else if (key == KEY_UP && MAIN_FRAME.pos_y == 0 && MAIN_FRAME.pos_line >= 1)
	{
		MAIN_FRAME.pos_line = MAIN_FRAME.pos_line - 1;
		if ((POSX + POSC) > strlen(MAIN_FRAME.lines[read_y()]))
		{
			POSX = strlen(MAIN_FRAME.lines[read_y()]) % calc_max_x();
			POSC = strlen(MAIN_FRAME.lines[read_y()]) - POSX;
		}
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
		if ((POSX + POSC) > strlen(MAIN_FRAME.lines[read_y()]))
		{
			POSX = strlen(MAIN_FRAME.lines[read_y()]) % calc_max_x();
			POSC = strlen(MAIN_FRAME.lines[read_y()]) - POSX;
		}
		draw_window();
		update_move_window();
		return 1;
	}
	else if (key == KEY_DOWN && POSY >= (size_y() - 2) && MAIN_FRAME.line_count > (POSY + MAIN_FRAME.pos_line))
	{
		if ((POSX + POSC) > strlen(MAIN_FRAME.lines[read_y()]))
		{
			POSX = strlen(MAIN_FRAME.lines[read_y()]) % calc_max_x();
			POSC = strlen(MAIN_FRAME.lines[read_y()]) - POSX;
		}
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

#ifdef DEBUG
int key_editor_quit(int key)
{
	if (key == STRG('d'))
	{
		sys_quit();
		return 1;
	}
	return 0;
}
#endif

int key_editor_backspace(int key)
{
	if(key == KEY_BACKSPACE)
	{
		
		set_was_edit(1);
		remove_for_char_monitor();
		draw_window();
		return 1;
	}
	return 0;
}

int key_hexshow_up(int key)
{
	if (key == KEY_UP && HEX_FRAME.posy > 0)
	{
		HEX_FRAME.posy = HEX_FRAME.posy - 1;
		draw_hex_window();
		return 1;
	}
	return 0;
}

int key_hexshow_down(int key)
{
	if (key == KEY_DOWN && (HEX_FRAME.posy + size_y()) < hex_max_size())
	{
		HEX_FRAME.posy = HEX_FRAME.posy + 1;
		draw_hex_window();
		return 1;
	}
	return 0;
}

int key_hexshow_close(int key)
{
	if (key == 'q')
	{
		close_hexshow();
		draw_window();
		return 1;
	}
	return 0;
}

void key_command_mode_save()
{
	save_window_file();
}

void key_command_mode_quit()
{
	if (!was_edit)
		sys_quit();
}

void key_command_mode_console()
{
	sys_console_open();
}

void key_command_mode_top_new_line()
{
	set_was_edit(1);
	add_line_monitor(1);
}

void key_command_mode_bottom_new_line()
{
	set_was_edit(1);
	add_line_monitor(2);
}

void key_command_mode_delete_line()
{
	set_was_edit(1);
	int pos = POSX;
	POSX = 1;
	delete_line_monitor();
	if (strlen(MAIN_FRAME.lines[read_y()]) <= pos)
		POSX = strlen(MAIN_FRAME.lines[read_y()]);
	else
		POSX = pos;
}

void key_command_mode_line_start()
{
	POSX = 0;
	POSC = 0;
}

void key_command_mode_line_end()
{
	if (strlen(MAIN_FRAME.lines[read_y()]) > calc_max_x())
		POSC = strlen(MAIN_FRAME.lines[read_y()]) - calc_max_x();
	POSX = strlen(MAIN_FRAME.lines[read_y()]) - POSC - 1;
}

void key_command_mode_upper_case()
{
	set_was_edit(1);
	char_array_upper_case(MAIN_FRAME.lines[read_y()]);
}

void key_command_mode_lower_case()
{
	set_was_edit(1);
	char_array_lower_case(MAIN_FRAME.lines[read_y()]);
}

void key_command_mode_line_top()
{
	POSY = (MAIN_FRAME.line_count - 1) % size_y();
	POSL = (MAIN_FRAME.line_count - 1) - POSY;
}

void key_command_mode_line_bottom()
{
	POSY = 0;
	POSL = 0;
}

void key_command_mode_delete_befor()
{
	set_was_edit(1);
	char* text = string_from_to(MAIN_FRAME.lines[read_y()], read_x(), strlen(MAIN_FRAME.lines[read_y()]));
	free(MAIN_FRAME.lines[read_y()]);
	MAIN_FRAME.lines[read_y()] = text;
	POSX = 0;
	POSC = 0;
}

void key_command_mode_delete_after()
{
	set_was_edit(1);
	char* text = string_from_to(MAIN_FRAME.lines[read_y()],0 ,read_x());
	free(MAIN_FRAME.lines[read_y()]);
	MAIN_FRAME.lines[read_y()] = text;
	POSX = strlen(MAIN_FRAME.lines[read_y()]) % size_y();
	POSC = strlen(MAIN_FRAME.lines[read_y()]) - POSX;
}

void key_command_mode_hex_show()
{
	init_hexshow();
}

void key_command_mode_force_quit()
{
	sys_quit();
}
