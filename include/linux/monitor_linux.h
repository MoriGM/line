#ifndef MONITOR_LINUX_H
#define MONITOR_LINUX_H

struct
{
	char** lines;
	int line_count, pos_y, pos_x, pos_line, pos_column;
} 
MAIN_FRAME;

void init_monitor(void);
void add_char_monitor(char c);
void delete_line_monitor(void);
void remove_char_monitor(void);
void remove_for_char_monitor(void);
void add_line_to_bevor_monitor(void);
/*
* 0 = Normale
* 1 = Top
* 2 = Bottom
*/
void add_line_monitor(unsigned int bevor);
void save_window_file(void);


#define CPOSY MAIN_FRAME.lines[read_y()]
#define SCPOSY strlen(MAIN_FRAME.lines[read_y()])
#define POSY MAIN_FRAME.pos_y
#define POSX MAIN_FRAME.pos_x
#define POSL MAIN_FRAME.pos_line
#define POSC MAIN_FRAME.pos_column


#define AFTER_SYSTEM do \
			{ \
				mem_free_char_array_array(MAIN_FRAME.lines, MAIN_FRAME.line_count); \
				MAIN_FRAME.lines = malloc(sizeof(char*) * 1000); \
				for (int i = 0;i < count;i++) \
				{ \
					MAIN_FRAME.lines[i] = MSOCHARARR; \
					MAIN_FRAME.lines[i][0] = '\0';\
					strcpy(MAIN_FRAME.lines[i], tmp[i]); \
				} \
				MAIN_FRAME.line_count = count; \
			}while(0)

#endif
