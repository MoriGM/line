#ifndef WINDOW_LINUX_H
#define WINDOW_LINUX_H

void start_window();
void draw_window();
void update_move_window();
void quit_window();
void size_window(int *y,int *x);
int size_y();
int size_x();
int calc_x();
int read_y();
int read_x();
int calc_max_x();

#endif
