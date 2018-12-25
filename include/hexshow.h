#ifndef HEXSHOW_H
#define HEXSHOW_H

struct
{
	char* line;
	int posy, pos;
} HEX_FRAME;

void init_hexshow();
int hex_max_size();
int hex_last_line();
int hex_posy();
int hex_last_line();
void draw_hex_window();
void close_hexshow();

#endif
