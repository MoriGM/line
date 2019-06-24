#ifndef SYS_FILE_H
#define SYS_FILE_H

struct file_data
{
	char** file_text;
	int file_len;
};


int has_file_arg(void);
char* get_file_arg(void);
struct file_data* create_file(void);
void add_line_to_file(struct file_data *fd, char* text);
struct file_data* load_arg_file(void);
struct file_data* read_file(char* file);
void write_file(char* file_text,struct file_data *file_write);

#endif
