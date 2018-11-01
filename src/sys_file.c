#include "nonamedef.h"
#include <stdio.h>

int has_file_arg()
{
	return has_arg_or_short_arg("-f", "-file");
}

char* get_file_arg()
{
	return get_argv()[has_file_arg() + 1];
}

void write_file(char* file_text,struct file_data file_write)
{
	FILE* file = fopen(file_text, "w");
	int i;
	for (i = 0;i < file_write.file_len;i++)
		fprintf(file, (i ? "\n%s" : "%s"), file_write.file_text[i]);
	fclose(file);
} 

struct file_data* read_file(char* file_text)
{
	FILE *file = fopen(file_text, "r");
	struct file_data *file_read = malloc(sizeof(struct file_data));
	file_read->file_text = MSOCHARARR;
	file_read->file_text[0] = MSOCHARARR;
	file_read->file_text[0][0] = '\0';
	file_read->file_len = 0;
	if(file == NULL || feof(file))
		return file_read;
	do
	{
		char i;
		fscanf(file,"%c",&i);
		if (feof(file))
			break;
		char tmp_for_this[3] = {i, '\0'};
		if (i == '\n')
		{
			file_read->file_len = file_read->file_len + 1;
			file_read->file_text[file_read->file_len] = MSOCHARARR;
			file_read->file_text[file_read->file_len][0] = '\0';
			
		}
		else
			strcat(file_read->file_text[file_read->file_len], tmp_for_this);
	}
	while (!feof(file));

	add(file_read->file_len, 1);
	
	fclose(file);

	return file_read;
}

struct file_data* load_arg_file()
{
	return read_file(get_file_arg());
}
