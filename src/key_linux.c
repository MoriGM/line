#include <nonamedef.h>

void key_listener()
{
	int c = getch();
	
	extern int was_edit;
	extern int command_mode;

	if (command_mode && !is_banned_key(c))
	{
		if (c == 's')
			save_window_file();
		command_mode = FALSE;
		draw_window();
		return;
	}

	if (c == KEY_UP && MAIN_FRAME.pos_y >= 1)
	{
		MAIN_FRAME.pos_y = MAIN_FRAME.pos_y - 1;
		if (MAIN_FRAME.pos_x > strlen(MAIN_FRAME.lines[MAIN_FRAME.pos_y]))
			MAIN_FRAME.pos_x = strlen(MAIN_FRAME.lines[MAIN_FRAME.pos_y]); 
		update_move_window();
	}
	else if (c == KEY_DOWN && (size_y() - 1) > POSY && (MAIN_FRAME.line_count - 1) > read_y())
	{
		MAIN_FRAME.pos_y = MAIN_FRAME.pos_y + 1;
		if (MAIN_FRAME.pos_x > strlen(MAIN_FRAME.lines[read_y()]))
			MAIN_FRAME.pos_x = strlen(MAIN_FRAME.lines[read_y()]);
		update_move_window();
	}
	else if (c == KEY_LEFT && MAIN_FRAME.pos_x >= 1)
	{
		POSX = POSX - 1;
		update_move_window();
	}
	else if (c == KEY_RIGHT && POSX < size_x()  && MAIN_FRAME.pos_x < strlen(MAIN_FRAME.lines[read_y()]))
	{	
		MAIN_FRAME.pos_x = MAIN_FRAME.pos_x + 1;
		update_move_window();
	}
	else if (c == KEY_UP && MAIN_FRAME.pos_y == 0 && MAIN_FRAME.pos_line >= 1)
	{
		MAIN_FRAME.pos_line = MAIN_FRAME.pos_line - 1;
		draw_window();
	}
	else if (c == KEY_DOWN && POSY >= (size_y() - 2) && MAIN_FRAME.line_count > (POSY + MAIN_FRAME.pos_line))
	{
		POSL = POSL + 1;
		draw_window();
	}
	else if (c == KEY_RIGHT && POSX == size_x() && (POSC + size_x()) <= strlen(MAIN_FRAME.lines[read_y()]))
	{
		POSC = POSC + 1;
		draw_window();
		move(POSY, size_x() - 1);
	}
	else if (c == KEY_LEFT && POSX == 0 && POSC >= 1)
	{
		POSC = POSC - 1;
		draw_window();
		move(POSY, 0);
	}
	else if (c == KEY_ENTER || c == '\n')
	{
		add_line_monitor(0);
		draw_window();
		was_edit = TRUE;
	}
	else if(c == KEY_BACKSPACE)
	{
		remove_for_char_monitor();
		draw_window();
		was_edit = TRUE;
	}
	else if (c == STRG('d'))
	{
		sys_quit();
	}
	else if (c == STRG('x'))
	{
		command_mode = TRUE;
		draw_window();
	}
	else if (!is_banned_key(c))
	{
		add_char_monitor(c); 
		draw_window();
		was_edit = TRUE;
	}
}

int is_banned_key(int c)
{
	return c == KEY_DOWN || c == KEY_UP || c == KEY_LEFT || c == KEY_RIGHT || c == STRG('c') || c == STRG('s');
}
