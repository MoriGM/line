#ifndef HEXSHOW_H
#define HEXSHOW_H

struct
{
	char* line;
	int posy, pos;
} HEX_FRAME;

void init_hexshow(void);
int hex_max_size(void);
int hex_last_line(void);
int hex_posy(void);
int hex_last_line(void);
void draw_hex_window(void);
void close_hexshow(void);

#endif
