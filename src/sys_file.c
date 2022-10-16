#include <nonamedef.h>

char* get_file_arg(void)
{
	return get_argv()[get_argc() - 1];
}

struct file_data* create_file(void)
{
	struct file_data *fd = malloc(sizeof(struct file_data));
	fd->file_text = malloc(sizeof(char*));
	fd->file_text[0] = malloc(sizeof(char));
	fd->file_text[0][0] = '\0';

	fd->file_len = 0;

	return fd;
}

void add_line_to_file(struct file_data *fd, char* text)
{
	fd->file_text[fd->file_len] = realloc(fd->file_text[fd->file_len], sizeof(char) * (strlen(text) + 1));
	strcpy(fd->file_text[fd->file_len], text);
	fd->file_len = fd->file_len + 1;
	fd->file_text = realloc(fd->file_text, sizeof(char*) * (fd->file_len + 1));
	fd->file_text[fd->file_len] = malloc(sizeof(char));
	fd->file_text[fd->file_len][0] = '\0';
}

void write_file(char* file_text,struct file_data *file_write)
{
	FILE* file = fopen(file_text, "w");
	int i;
	for (i = 0;i < file_write->file_len;i++)
		fprintf(file, (i ? "\n%s" : "%s"), file_write->file_text[i]);
	fclose(file);
} 

struct file_data* read_file(char* file_text)
{
	FILE *file = fopen(file_text, "r");
	struct file_data *file_read = malloc(sizeof(struct file_data));
	file_read->file_text = malloc(sizeof(char*));
	file_read->file_text[0] = malloc(sizeof(char));
	file_read->file_text[0][0] = '\0';
	file_read->file_len = 0;

	if(file == NULL || feof(file))
	{
		file_read->file_len = 1;
		return file_read;
	}

	do
	{
		char i;
		fscanf(file,"%c",&i);
		if (feof(file)) break;
		if (i == '\n')
		{
			file_read->file_len += 1;
			file_read->file_text = realloc(file_read->file_text, sizeof(char*) * (file_read->file_len + 1));
			file_read->file_text[file_read->file_len] = malloc(sizeof(char));
			file_read->file_text[file_read->file_len][0] = '\0';
		}
		else
		{
			int len = strlen(file_read->file_text[file_read->file_len]);
			file_read->file_text[file_read->file_len] = realloc(file_read->file_text[file_read->file_len], (len + 2) * sizeof(char));
			file_read->file_text[file_read->file_len][len] = i;
			file_read->file_text[file_read->file_len][len + 1] = '\0';
		}
	}
	while (!feof(file));

	file_read->file_len = file_read->file_len + 1;
	
	fclose(file);

	return file_read;
}

struct file_data* load_arg_file(void)
{
	return read_file(get_file_arg());
}
