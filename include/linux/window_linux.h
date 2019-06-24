#ifndef WINDOW_LINUX_H
#define WINDOW_LINUX_H

void start_window(void);
void draw_window(void);
void update_move_window(void);
void quit_window(void);
void clear_screen(void);
void size_window(int *y,int *x);
int size_y(void);
int size_x(void);
int calc_x(void);
int read_y(void);
int read_x(void);
int calc_max_x(void);
void add_draw_bottom_text(char* text);
void clear_bottom_text(void);
void render_bottom_text(void);
void generate_bottom_text(void);
void generate_command_key_bottom_text(void);

#endif
