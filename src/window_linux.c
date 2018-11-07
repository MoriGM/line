#include <nonamedef.h>

int x,y;

extern int syntax_hl;

void start_window()
{
	initscr();
	init_colormode();
	move(0,0);
	noecho();
	keypad(stdscr, 1);
}

int get_new_max_line()
{
	if((MAIN_FRAME.line_count - MAIN_FRAME.pos_line) >= size_y())
		return MAIN_FRAME.pos_line + size_y();
	else
		return MAIN_FRAME.line_count;
}

void draw_window()
{
	clear();
	if (has_colormode() && has_arg_syntax_file() && syntax_hl)
		for (int i = MAIN_FRAME.pos_line;i < get_new_max_line();i++)
		{
			char* cc = string_from_to(MAIN_FRAME.lines[i],POSC ,(POSC + calc_max_x()));
			draw_char_array(cc);
			free(cc);
		}
	else
		for(int i = MAIN_FRAME.pos_line;i < get_new_max_line();i++)
		{
			char* cc = string_from_to(MAIN_FRAME.lines[i], POSC,(POSC + calc_max_x()));
			printw("%s\n", cc);
			free(cc);
		}
	extern int command_mode;

	extern int was_edit;

	if (was_edit)
		set_draw_bottom_text("*");

	if (command_mode)
		set_draw_bottom_text("Command Mode");

	update_move_window();
	refresh();
}

void update_move_window()
{
	move(POSY, calc_x());
}

void quit_window()
{
	endwin();
}

void size_window(int *y,int *x)
{
	getmaxyx(stdscr, *y, *x);
}

int size_y()
{
	int y,x;
	size_window(&y, &x);
	return (y - 1);
}

int size_x()
{
	int y,x;
	size_window(&y, &x);
	return x;
}

int read_x()
{
	return POSC + POSX;
}

int calc_max_x()
{
	return size_x();
}

int calc_x()
{
	int calc = 0;
	for(int i = 0; i < POSX; i++)
		if(CPOSY[i] == '\t')
			calc += 8;
		else
			calc += 1;
	return calc;
}

int read_y()
{
	return MAIN_FRAME.pos_y + MAIN_FRAME.pos_line;
}


void set_draw_bottom_text(char* text)
{
	move(size_y(),0);
	printw("%s ", text);
	update_move_window();

}
