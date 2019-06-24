#ifndef KEY_MAP_H
#define KEY_MAP_H

void key_editor_left(void);
void key_editor_command_mode(void);
#ifdef DEBUG
void key_editor_quit(void);
#endif
void key_editor_enter(void);
void key_editor_up(void);
void key_editor_down(void);
void key_editor_right(void);
void key_editor_backspace(void);
void key_hexshow_up(void);
void key_hexshow_down(void);
void key_hexshow_close(void);
void key_command_mode_save(void);
void key_command_mode_quit(void);
void key_command_mode_console(void);
void key_command_mode_top_new_line(void);
void key_command_mode_bottom_new_line(void);
void key_command_mode_delete_line(void);
void key_command_mode_line_start(void);
void key_command_mode_line_end(void);
void key_command_mode_upper_case(void);
void key_command_mode_lower_case(void);
void key_command_mode_line_top(void);
void key_command_mode_line_bottom(void);
void key_command_mode_delete_befor(void);
void key_command_mode_delete_after(void);
void key_command_mode_hex_show(void);
void key_command_mode_force_quit(void);

#endif
