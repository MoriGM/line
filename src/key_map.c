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

int key_command_mode_top_new_line(int key[], int len)
{
	if (len == 1 && key[0] == 'O')
	{
		set_was_edit(1);
		add_line_monitor(1);
		return 1;
	}
	return 0;
}

int key_command_mode_bottom_new_line(int key[], int len)
{
	if (len == 1 && key[0] == 'o')
	{
		set_was_edit(1);
		add_line_monitor(2);
		return 1;
	}
	return 0;
}

int key_command_mode_delete_line(int key[], int len)
{
	if (len == 2 && key[0] == 'd' && key[1] == 'l')
	{
		set_was_edit(1);
		int pos = POSX;
		POSX = 1;
		delete_line_monitor();
		if (strlen(MAIN_FRAME.lines[read_y()]) <= pos)
			POSX = strlen(MAIN_FRAME.lines[read_y()]);
		else
			POSX = pos;
		return 1;
	}
	return 0;
}

int key_command_mode_line_start(int key[], int len)
{
	if (len == 2 && key[0] == 'l' && key[1] == 's')
	{
		POSX = 0;
		POSC = 0;
		return 1;
	}
	return 0;
}

int key_command_mode_line_end(int key[], int len)
{
	if (len == 2 && key[0] == 'l' && key[1] == 'e')
	{
		if (strlen(MAIN_FRAME.lines[read_y()]) > calc_max_x())
			POSC = strlen(MAIN_FRAME.lines[read_y()]) - calc_max_x();
		POSX = strlen(MAIN_FRAME.lines[read_y()]) - POSC - 1;
		return 1;
	}
	return 0;
}

int key_command_mode_upper_case(int key[], int len)
{
	if (len == 3 && key[0] == 'l' && key[1] == 'u' && key[2] == 'c')
	{
		set_was_edit(1);
		char_array_upper_case(MAIN_FRAME.lines[read_y()]);
		return 1;
	}
	return 0;
}

int key_command_mode_lower_case(int key[], int len)
{
	if (len == 3 && key[0] == 'l' && key[1] == 'l' && key[2] == 'c')
	{
		set_was_edit(1);
		char_array_lower_case(MAIN_FRAME.lines[read_y()]);
		return 1;
	}
	return 0;
}

int key_command_mode_line_top(int key[], int len)
{
	if (len == 2 && key[0] == 'l' && key[1] == 't')
	{
		POSY = (MAIN_FRAME.line_count - 1) % size_y();
		POSL = (MAIN_FRAME.line_count - 1) - POSY;
		return 1;
	}
	return 0;
}

int key_command_mode_line_bottom(int key[], int len)
{
	if (len == 2 && key[0] == 'l' && key[1] == 'b')
	{
		POSY = 0;
		POSL = 0;
		return 1;
	}
	return 0;
}

int key_command_mode_delete_befor(int key[], int len)
{
	if (len == 2 && key[0] == 'd' && key[1] == 'b')
	{
		set_was_edit(1);
		char* text = string_from_to(MAIN_FRAME.lines[read_y()], read_x(), strlen(MAIN_FRAME.lines[read_y()]));
		free(MAIN_FRAME.lines[read_y()]);
		MAIN_FRAME.lines[read_y()] = text;
		POSX = 0;
		POSC = 0;
		return 1;
	}
	return 0;
}

int key_command_mode_delete_after(int key[], int len)
{
	if (len == 2 && key[0] == 'd' && key[1] == 'a')
	{
		set_was_edit(1);
		char* text = string_from_to(MAIN_FRAME.lines[read_y()],0 ,read_x());
		free(MAIN_FRAME.lines[read_y()]);
		MAIN_FRAME.lines[read_y()] = text;
		POSX = strlen(MAIN_FRAME.lines[read_y()]) % size_y();
		POSC = strlen(MAIN_FRAME.lines[read_y()]) - POSX;

		return 1;
	}
	return 0;
}

int key_command_mode_hex_show(int key[], int len)
{
	if (len == 3 && key[0] == 'h' && key[1] == 'e' && key[2] == 'x')
	{
		init_hexshow();
		return 1;
	}
	return 0;
}

int key_command_mode_force_quit(int key[], int len)
{
	if (len == 1 && key[0] == 'Q')
	{
		sys_quit();
		return 1;
	}
	return 0;
}
