#ifndef KEY_MAP_H
#define KEY_MAP_H

int key_editor_left(int key);
int key_editor_command_mode(int key);
#ifdef DEBUG
int key_editor_quit(int key);
#endif
int key_editor_enter(int key);
int key_editor_up(int key);
int key_editor_down(int key);
int key_editor_right(int key);
int key_editor_backspace(int key);
int key_hexshow_up(int key);
int key_hexshow_down(int key);
int key_hexshow_close(int key);
void key_command_mode_save();
void key_command_mode_quit();
void key_command_mode_console();
void key_command_mode_top_new_line();
void key_command_mode_bottom_new_line();
void key_command_mode_delete_line();
void key_command_mode_line_start();
void key_command_mode_line_end();
void key_command_mode_upper_case();
void key_command_mode_lower_case();
void key_command_mode_line_top();
void key_command_mode_line_bottom();
void key_command_mode_delete_befor();
void key_command_mode_delete_after();
void key_command_mode_hex_show();
void key_command_mode_force_quit();

#endif
