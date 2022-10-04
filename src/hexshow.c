#include <nonamedef.h>

struct hex_frame_struct HEX_FRAME;

void init_hexshow(void)
{
	move(0, 0);
	HEX_FRAME.line = malloc(sizeof(char));
	HEX_FRAME.text = malloc(sizeof(char));
	int pos = 0, text_pos = 0;
	for (int i = 0;i < MAIN_FRAME.line_count;i++)
		for (int p = 0; p < strlen(MAIN_FRAME.lines[i]);p++)
		{
			char* cc = char_to_hex(MAIN_FRAME.lines[i][p]);
			HEX_FRAME.line = realloc(HEX_FRAME.line, sizeof(char) * (pos + 3));
			HEX_FRAME.line[pos++] = cc[0];
			HEX_FRAME.line[pos++] = cc[1];
			mem_free_char_array(cc);
			HEX_FRAME.text = realloc(HEX_FRAME.text, sizeof(char) * (text_pos + 2));
			HEX_FRAME.text[text_pos++] = hex_to_char(MAIN_FRAME.lines[i][p]);
		}
	HEX_FRAME.line[pos] = '\0';
	HEX_FRAME.text[text_pos] = '\0';
	HEX_FRAME.pos = pos;
	key_type = HEXSHOW;
	HEX_FRAME.posy = 0;
}

int hex_max_size(void)
{
	int line_count = HEX_FRAME.pos / 2;
	int extra_line = line_count % 16;
	line_count = line_count / 16;

	if (extra_line) line_count++;

	return line_count;
}

int hex_last_line(void)
{
	int line_count = HEX_FRAME.pos / 2;
	int extra_line = line_count % 16;

	return extra_line;
}

int hex_posy(void)
{
	return HEX_FRAME.posy * 32;
}

void draw_hex_window(void)
{
	int run = 0, line = 0, space = 0, text_len = (hex_posy() / 2), text_len_start = text_len;

	clear();

	move(0, 0);

	char* tmp = int_to_hex(HEX_FRAME.posy);

	printw("%s0 ", tmp);
	
	free(tmp);

	for (int i = hex_posy();i < HEX_FRAME.pos;i++)
	{
		printw("%c", HEX_FRAME.line[i]);
		run++;
		space++;

		if (run % 2 == 0) text_len++;

		if (space == 4 && run < 32)
		{
			printw(" ");
			space = 0;
		}
		if (run >= 32)
		{
			line++;
			printw(" ");
			for (int ti = text_len_start;ti < text_len;ti++) printw("%c", HEX_FRAME.text[ti]);
			text_len_start = text_len;
			printw("\n");
			run = 0;
			space = 0;
			if (line < size_y())
			{
				tmp = int_to_hex(HEX_FRAME.posy + line);
				printw("%s0 ", tmp);
				free(tmp);
			}
		}
		if (line >= size_y())
			break;
	}
	space--;
	for (int i = run; i <= 32;i++,space++) 
	{
		if (space == 4)
		{
		 	printw(" ");
			space = 0;
		}
		printw(" ");
	}
	for (int ti = text_len_start;ti < text_len;ti++) printw("%c", HEX_FRAME.text[ti]);

	move(0, 0);
}


void close_hexshow(void)
{
	mem_free_char_array(HEX_FRAME.line);
	mem_free_char_array(HEX_FRAME.text);
	update_move_window();
	key_type = EDITOR;
}

char hex_to_char(char c)
{
	if (c > 0x7E || c < 0x20) return '.';
	return c;
}
