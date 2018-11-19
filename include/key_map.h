#ifndef KEY_MAP_H
#define KEY_MAP_H

int key_editor_left(int key);
int key_editor_command_mode(int key);
int key_editor_quit(int key);
int key_editor_enter(int key);
int key_editor_up(int key);
int key_editor_down(int key);
int key_editor_right(int key);
int key_editor_backspace(int key);
int key_command_mode_save(int key[], int len);
int key_command_mode_quit(int key[], int len);
int key_command_mode_console(int key[], int len);
int key_command_mode_top_new_line(int key[], int len);
int key_command_mode_bottom_new_line(int key[], int len);


#endif
