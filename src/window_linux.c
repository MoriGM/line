#include <nonamedef.h>

int x,y;

extern int syntax_hl;

void start_window(void)
{
	initscr();
	init_colormode();
	move(0,0);
	noecho();
	keypad(stdscr, 1);
}

int get_new_max_line(void)
{
	if((MAIN_FRAME.line_count - MAIN_FRAME.pos_line) >= size_y())
		return MAIN_FRAME.pos_line + size_y();
	else
		return MAIN_FRAME.line_count;
}

void draw_window(void)
{
	clear_screen();

	if (has_colormode() && has_arg_syntax_file() && syntax_hl)
		for (int i = MAIN_FRAME.pos_line;i < get_new_max_line();i++)
		{
			if (strlen(MAIN_FRAME.lines[i]) < POSC)
			{
				printw("\n");
				continue;
			}
			char* cc = string_from_to(MAIN_FRAME.lines[i],POSC ,(POSC + calc_max_x()));
			draw_char_array(cc);
			free(cc);
		}
	else if (key_type == EDITOR)
		for(int i = MAIN_FRAME.pos_line;i < get_new_max_line();i++)
		{
			if (strlen(MAIN_FRAME.lines[i]) < POSC)
			{
				printw("\n");
				continue;
			}
			char* cc = string_from_to(MAIN_FRAME.lines[i], POSC,(POSC + calc_max_x()));
			printw("%s\n", cc);
			free(cc);
		}
	else if (key_type == HEXSHOW)
		draw_hex_window();

	generate_bottom_text();

	render_bottom_text();
	
	if (key_type == EDITOR)
		update_move_window();

	refresh();
}

void update_move_window(void)
{
	move(POSY, calc_x());
}

void quit_window(void)
{
	endwin();
}

void clear_screen(void)
{
	clear();
	clear_bottom_text();
}

void size_window(int *y,int *x)
{
	getmaxyx(stdscr, *y, *x);
}

int size_y(void)
{
	int y,x;
	size_window(&y, &x);
	return (y - 1);
}

int size_x(void)
{
	int y,x;
	size_window(&y, &x);
	return x;
}

int read_x(void)
{
	return POSC + POSX;
}

int calc_max_x(void)
{
	return size_x() - 2;
}

int calc_x(void)
{
	int calc = 0;
	for(int i = 0; i < POSX; i++)
		if(CPOSY[i] == '\t')
			calc += 8;
		else
			calc += 1;
	return calc;
}

int read_y(void)
{
	return MAIN_FRAME.pos_y + MAIN_FRAME.pos_line;
}

void clear_bottom_text(void)
{
	extern char* bottom_text;
	strcpy(bottom_text, "");
}

void add_draw_bottom_text(char* text)
{
	extern char* bottom_text;
	strcat(bottom_text, text);
	strcat(bottom_text, " ");
}

void render_bottom_text(void)
{
	extern char* bottom_text;
	move(size_y(), 0);
	printw("%s", bottom_text);
}

void generate_bottom_text(void)
{
	extern int command_mode;
	extern int was_edit;
	extern int command_mode_key_len; 

	if (was_edit)
		add_draw_bottom_text("*");
	if (command_mode)
		add_draw_bottom_text("Command Mode");
	if (command_mode_key_len)
		generate_command_key_bottom_text();
}

void generate_command_key_bottom_text(void)
{
	extern int command_mode_key[];
	extern int command_mode_key_len;
	char* ft = malloc(sizeof(char) * 5);
	
	if (command_mode_key_len == 1)
	{ft[0] = command_mode_key[0];ft[1] = '\n';}
	if (command_mode_key_len == 2)
	{ft[0] = command_mode_key[0];ft[1] = command_mode_key[1];ft[2] = '\n';}

	add_draw_bottom_text(ft);
	free(ft);
}
