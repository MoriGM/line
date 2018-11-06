#include <nonamedef.h>

void mem_free_char_array(char* c)
{
	free(c);
}

void mem_free_char_array_array(char** c,int count)
{
	for (int i = 0;i < count;i++)
		free(c[i]);
	free(c);
}

void mem_free_file_data(struct file_data *fd)
{
	for (int i = 0;i < fd->file_len;i++)
		free(fd->file_text[i]);
	free(fd->file_text);
	free(fd);
}

void mem_free_split_string(struct split_string *ss)
{
	for (int i = 0;i < ss->line_count;i++)
		free(ss->lines[i]);
	free(ss->lines);
}
