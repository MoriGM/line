#ifndef WINDOW_LINUX_H
#define WINDOW_LINUX_H

void start_window();
void draw_window();
void update_move_window();
void quit_window();
void clear_screen();
void size_window(int *y,int *x);
int size_y();
int size_x();
int calc_x();
int read_y();
int read_x();
int calc_max_x();
void add_draw_bottom_text(char* text);
void clear_bottom_text();
void render_bottom_text();
void generate_bottom_text();
void generate_command_key_bottom_text();

#endif
