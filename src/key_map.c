#include <nonamedef.h>

extern int command_mode;
extern int was_edit;

void key_editor_left(void)
{
	if (MAIN_FRAME.pos_x >= 1)
	{
		POSX = POSX - 1;
		update_move_window();
	}
	else if (POSX == 0 && POSC >= 1)
	{
		POSC = POSC - 1;
		draw_window();
		move(POSY, 0);
	}
}

void key_editor_enter(void)
{
	set_was_edit(1);
	add_line_monitor(0);
	draw_window();
}

void key_editor_up(void)
{
	if (MAIN_FRAME.pos_y >= 1)
	{
		MAIN_FRAME.pos_y = MAIN_FRAME.pos_y - 1;
		if ((POSX + POSC) > strlen(MAIN_FRAME.lines[read_y()]))
		{
			POSX = strlen(MAIN_FRAME.lines[read_y()]) % calc_max_x();
			POSC = strlen(MAIN_FRAME.lines[read_y()]) - POSX;
		}
		update_move_window();
	}
	else if (MAIN_FRAME.pos_y == 0 && MAIN_FRAME.pos_line >= 1)
	{
		MAIN_FRAME.pos_line = MAIN_FRAME.pos_line - 1;
		if ((POSX + POSC) > strlen(MAIN_FRAME.lines[read_y()]))
		{
			POSX = strlen(MAIN_FRAME.lines[read_y()]) % calc_max_x();
			POSC = strlen(MAIN_FRAME.lines[read_y()]) - POSX;
		}
		draw_window();
	}
}

void key_editor_down(void)
{
	if ((size_y() - 1) > POSY && (MAIN_FRAME.line_count - 1) > read_y())
	{
		MAIN_FRAME.pos_y = MAIN_FRAME.pos_y + 1;
		if ((POSX + POSC) > strlen(MAIN_FRAME.lines[read_y()]))
		{
			POSX = strlen(MAIN_FRAME.lines[read_y()]) % calc_max_x();
			POSC = strlen(MAIN_FRAME.lines[read_y()]) - POSX;
		}
		draw_window();
		update_move_window();
	}
	else if (POSY >= (size_y() - 2) && MAIN_FRAME.line_count > (POSY + MAIN_FRAME.pos_line))
	{
		if ((POSX + POSC) > strlen(MAIN_FRAME.lines[read_y()]))
		{
			POSX = strlen(MAIN_FRAME.lines[read_y()]) % calc_max_x();
			POSC = strlen(MAIN_FRAME.lines[read_y()]) - POSX;
		}
		POSL = POSL + 1;
		draw_window();
	}
}

void key_editor_right(void)
{
	if (POSX < size_x() && MAIN_FRAME.pos_x < strlen(MAIN_FRAME.lines[read_y()]))
	{	
		MAIN_FRAME.pos_x = MAIN_FRAME.pos_x + 1;
		update_move_window();
	}
	else if (POSX == size_x() && (POSC + size_x()) <= strlen(MAIN_FRAME.lines[read_y()]))
	{
		POSC = POSC + 1;
		draw_window();
		move(POSY, size_x() - 1);
	}
}
	

void key_editor_command_mode(void)
{
	command_mode = TRUE;
	draw_window();
}

#ifdef DEBUG
void key_editor_quit(void)
{
	sys_quit();
}
#endif

void key_editor_backspace(void)
{
	set_was_edit(1);
	remove_for_char_monitor();
	draw_window();
}

void key_hexshow_up(void)
{
	if (HEX_FRAME.posy > 0)
	{
		HEX_FRAME.posy = HEX_FRAME.posy - 1;
		draw_hex_window();
	}
}

void key_hexshow_down(void)
{
	if ((HEX_FRAME.posy + size_y()) < hex_max_size())
	{
		HEX_FRAME.posy = HEX_FRAME.posy + 1;
		draw_hex_window();
	}
}

void key_hexshow_close(void)
{
	close_hexshow();
	draw_window();
}

void key_command_mode_save(void)
{
	save_window_file();
}

void key_command_mode_quit(void)
{
	if (!was_edit)
		sys_quit();
}

void key_command_mode_console(void)
{
	sys_console_open();
}

void key_command_mode_top_new_line(void)
{
	set_was_edit(1);
	add_line_monitor(1);
}

void key_command_mode_bottom_new_line(void)
{
	set_was_edit(1);
	add_line_monitor(2);
}

void key_command_mode_delete_line(void)
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

void key_command_mode_line_start(void)
{
	POSX = 0;
	POSC = 0;
}

void key_command_mode_line_end(void)
{
	if (strlen(MAIN_FRAME.lines[read_y()]) > calc_max_x())
		POSC = strlen(MAIN_FRAME.lines[read_y()]) - calc_max_x();
	POSX = strlen(MAIN_FRAME.lines[read_y()]) - POSC - 1;
}

void key_command_mode_upper_case(void)
{
	set_was_edit(1);
	char_array_upper_case(MAIN_FRAME.lines[read_y()]);
}

void key_command_mode_lower_case(void)
{
	set_was_edit(1);
	char_array_lower_case(MAIN_FRAME.lines[read_y()]);
}

void key_command_mode_line_top(void)
{
	POSY = (MAIN_FRAME.line_count - 1) % size_y();
	POSL = (MAIN_FRAME.line_count - 1) - POSY;
}

void key_command_mode_line_bottom(void)
{
	POSY = 0;
	POSL = 0;
}

void key_command_mode_delete_befor(void)
{
	set_was_edit(1);
	char* text = string_from_to(MAIN_FRAME.lines[read_y()], read_x(), strlen(MAIN_FRAME.lines[read_y()]));
	free(MAIN_FRAME.lines[read_y()]);
	MAIN_FRAME.lines[read_y()] = text;
	POSX = 0;
	POSC = 0;
}

void key_command_mode_delete_after(void)
{
	set_was_edit(1);
	char* text = string_from_to(MAIN_FRAME.lines[read_y()],0 ,read_x());
	free(MAIN_FRAME.lines[read_y()]);
	MAIN_FRAME.lines[read_y()] = text;
	POSX = strlen(MAIN_FRAME.lines[read_y()]) % size_y();
	POSC = strlen(MAIN_FRAME.lines[read_y()]) - POSX;
}

void key_command_mode_hex_show(void)
{
	init_hexshow();
}

void key_command_mode_force_quit(void)
{
	sys_quit();
}
