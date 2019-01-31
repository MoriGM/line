#include <nonamedef.h>

void init_hexshow()
{
	move(0, 0);
	HEX_FRAME.line = malloc(sizeof(char) * 100000);
	int pos = 0;
	for (int i = 0;i < MAIN_FRAME.line_count;i++)
		for (int p = 0; p < strlen(MAIN_FRAME.lines[i]);p++)
		{
			char* cc = char_to_hex(MAIN_FRAME.lines[i][p]);
			HEX_FRAME.line[pos++] = cc[1];
			HEX_FRAME.line[pos++] = cc[0];
			mem_free_char_array(cc);
		}
	HEX_FRAME.line[pos] = '\0';
	HEX_FRAME.pos = pos;
	key_type = HEXSHOW;
	HEX_FRAME.posy = 0;
}

int hex_max_size()
{
	int line_count = HEX_FRAME.pos / 2;
	int extra_line = line_count % 16;
	line_count = line_count / 16;

	if (extra_line)
		line_count++;

	return line_count;
}

int hex_last_line()
{
	int line_count = HEX_FRAME.pos / 2;
	int extra_line = line_count % 16;

	return extra_line;
}

int hex_posy()
{
	return HEX_FRAME.posy * 32;
}

void draw_hex_window()
{
	int run = 0, line = 0, space = 0;

	clear();

	move(0, 0);

	printw("%s0 ", int_to_hex(HEX_FRAME.posy));

	for (int i = hex_posy();i < HEX_FRAME.pos;i++)
	{
		printw("%c", HEX_FRAME.line[i]);
		run++;
		space++;
		if (space == 4 && run < 32)
		{
			printw(" ");
			space = 0;
		}
		if (run >= 32)
		{
			line++;
			printw("\n");
			run = 0;
			space = 0;
			if (line < size_y())
				printw("%s0 ", int_to_hex(HEX_FRAME.posy + line));
		}
		if (line >= size_y())
			break;
	}

	move(0, 0);
}


void close_hexshow()
{
	mem_free_char_array(HEX_FRAME.line);
	update_move_window();
	key_type = EDITOR;
}
