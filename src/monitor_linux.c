#include <nonamedef.h>

struct main_frame_struct MAIN_FRAME;

void init_monitor(void)
{
	MAIN_FRAME.pos_y = 0;
	MAIN_FRAME.pos_x = 0;
	MAIN_FRAME.pos_line = 0;
	MAIN_FRAME.pos_column = 0;
	if (has_file_arg())
	{
		struct file_data *arg_file = load_arg_file();
		MAIN_FRAME.lines = malloc(sizeof(char*) * arg_file->file_len);
		for (int i = 0;i < arg_file->file_len;i++)
		{
			MAIN_FRAME.lines[i] = malloc(sizeof(char) * (strlen(arg_file->file_text[i]) + 1));
			MAIN_FRAME.lines[i][0] = '\0';
			strcpy(MAIN_FRAME.lines[i], arg_file->file_text[i]);
		}
		MAIN_FRAME.line_count = arg_file->file_len;
		mem_free_file_data(arg_file);
	}
	else
	{
		MAIN_FRAME.lines = MSOCHARPARR;
		MAIN_FRAME.lines[0] = MSOCHARARR;
		MAIN_FRAME.lines[0][0] = '\0';
		MAIN_FRAME.line_count = 1;
	}
}

void add_char_monitor(char c)
{
	if (read_y() > MAIN_FRAME.line_count || MAIN_FRAME.lines[read_y()] == NULL || !MAIN_FRAME.lines[read_y()]) {
        return;
	}

	char* tmp = malloc(sizeof(char) * (strlen(MAIN_FRAME.lines[read_y()]) + 2));
	for (int i = 0;i < (POSX + POSC);i++) {
        if (MAIN_FRAME.lines[read_y()][i] != '\0'){
            tmp[i] = MAIN_FRAME.lines[read_y()][i];
        }
	}
	tmp[POSX + POSC] = c;
	for (int i = (POSX + POSC);i < strlen(MAIN_FRAME.lines[read_y()]);i++) {
        if (MAIN_FRAME.lines[read_y()][i] != '\0') {
            tmp[i + 1] = MAIN_FRAME.lines[read_y()][i];
        }
	}
	tmp[strlen(MAIN_FRAME.lines[read_y()]) + 1] = '\0';
	MAIN_FRAME.lines[read_y()] = realloc(MAIN_FRAME.lines[read_y()], sizeof(char) * (strlen(MAIN_FRAME.lines[read_y()]) + 2));
	strcpy(MAIN_FRAME.lines[read_y()], tmp);
	if (POSX <= calc_max_x()){
        POSX = POSX + 1;
	} else {
        POSC = POSC + 1;
	}
	free(tmp);
}

void delete_line_monitor(void)
{
	if (POSX == 0)
		return;

	char** tmp;
	int count = 0;
	tmp = MSOCHARPARR;
	for (int i = 0;i < MAIN_FRAME.line_count;i++)
	{
		if (i != (read_y()))
		{
			tmp[count] = MSOCHARARR;
			tmp[count][0] = '\0';
			strcat(tmp[count], MAIN_FRAME.lines[i]);
			count++;
		}
	}

	mem_free_char_array_array(MAIN_FRAME.lines, MAIN_FRAME.line_count);
	MAIN_FRAME.lines = malloc(sizeof(char*) * count);
	for (int i = 0;i < count;i++)
	{
		MAIN_FRAME.lines[i] = calloc((strlen(tmp[i]) + 1), sizeof(char));
		strcpy(MAIN_FRAME.lines[i], tmp[i]);
	}
	MAIN_FRAME.line_count = count;

	mem_free_char_array_array(tmp, count);
	if (POSY >= 1)
		POSY = POSY - 1;
	if (POSL >= 1)
		POSL = POSL - 1;
	POSX = strlen(MAIN_FRAME.lines[read_y()]) % size_x();
	POSC = strlen(MAIN_FRAME.lines[read_y()]) - POSX;
}

void remove_char_monitor(void)
{
	if (read_y() > MAIN_FRAME.line_count || MAIN_FRAME.lines[read_y()] == NULL || !MAIN_FRAME.lines[read_y()])
		return;
	if (!strlen(MAIN_FRAME.lines[read_y()]))
		delete_line_monitor();
	if (POSX == 0)
	 	return add_line_to_bevor_monitor();

	char* tmp = MSOCHARARR;
	tmp[0] = '\0';
	int count = 0;
	for (int i = 0;i < strlen(MAIN_FRAME.lines[read_y()]);i++)
	{
		if (i != (read_x()))
		{
			tmp[count] = MAIN_FRAME.lines[read_y()][i];
			count++;
		}
	}
	tmp[count - 1] = '\0';
	MAIN_FRAME.lines[read_y()] = realloc(MAIN_FRAME.lines[read_y()], sizeof(char) * (strlen(tmp) + 1));
	strcpy(MAIN_FRAME.lines[read_y()], tmp);
	if(POSX > strlen(tmp))
		POSX = strlen(tmp) + 1;
	if (POSX != 0)
		POSX = POSX - 1;
	mem_free_char_array(tmp);
}

void remove_for_char_monitor(void)
{
	if (read_y() > MAIN_FRAME.line_count || MAIN_FRAME.lines[read_y()] == NULL || !MAIN_FRAME.lines[read_y()])
		return;
	if (!strlen(MAIN_FRAME.lines[read_y()]))
		delete_line_monitor();
	if (POSX == 0)
	 	return add_line_to_bevor_monitor();

	char* tmp = MSOCHARARR;
	tmp[0] = '\0';
	for (int i = 0;i < strlen(MAIN_FRAME.lines[read_y()]);i++)
	{
		char c[3] = {MAIN_FRAME.lines[read_y()][i], '\0'};
		if (i != (read_x() - 1))
			strcat(tmp, c);
	}
	tmp[strlen(MAIN_FRAME.lines[read_y()]) - 1] = '\0';
	MAIN_FRAME.lines[read_y()] = realloc(MAIN_FRAME.lines[read_y()], sizeof(char) * (strlen(tmp) + 1));
	strcpy(MAIN_FRAME.lines[read_y()], tmp);
	if(POSX > strlen(tmp))
		POSX = strlen(tmp) + 1;
	if (POSX != 0)
		POSX = POSX - 1;
	free(tmp);
}

void add_line_to_bevor_monitor(void)
{
	if (POSY == 0)
		return;
	char** tmp;
	int count = 0, del;
	tmp = MSOCHARPARR;
	for (int i = 0;i < MAIN_FRAME.line_count;i++)
	{	
		if (read_y() != i)
		{
			tmp[count] = MSOCHARARR;
			tmp[count][0] = '\0';
			strcpy(tmp[count], MAIN_FRAME.lines[i]);
			count++;
		}
		else
		{
			strcat(tmp[count - 1], MAIN_FRAME.lines[i]);
			del = strlen(MAIN_FRAME.lines[i]);
		}
	}

	mem_free_char_array_array(MAIN_FRAME.lines, MAIN_FRAME.line_count);
	MAIN_FRAME.lines = malloc(sizeof(char*) * count);
	for (int i = 0;i < count;i++)
	{
		MAIN_FRAME.lines[i] = calloc((strlen(tmp[i]) + 1), sizeof(char));
		strcpy(MAIN_FRAME.lines[i], tmp[i]);
	}
	MAIN_FRAME.line_count = count;

	if (POSY >= 1) POSY = POSY - 1;
	else if (POSL >= 1) POSL = POSL - 1;
	POSX = strlen(MAIN_FRAME.lines[read_y()]) % size_x();
	POSC = strlen(MAIN_FRAME.lines[read_y()]) - POSX;
	POSX = POSX - del;
	mem_free_char_array_array(tmp, count);
}

void add_line_monitor(unsigned int bevor)
{

	char** tmp;
	int count = 0;
	int pos = read_y();
	tmp = MSOCHARPARR;
	for (int i = 0;i < MAIN_FRAME.line_count;i++)
	{
		if (i != pos)
		{
			tmp[count] = MSOCHARARR;
			tmp[count][0] = '\0';
			strcpy(tmp[count], MAIN_FRAME.lines[i]);
			count++;
		}
		else
		{
			if (bevor == 0)
			{
				tmp[count] = MSOCHARARR;
				tmp[count][0] = '\0';
				for (int x = 0;x < POSX;x++)
				{
					char c[3] = {MAIN_FRAME.lines[i][x], '\0'};
					strcat(tmp[count], c);
				}
				count++;
				tmp[count] = MSOCHARARR;
				tmp[count][0] = '\0';
				for (int x = POSX;x < strlen(MAIN_FRAME.lines[i]);x++)
				{
					char c[3] = {MAIN_FRAME.lines[i][x], '\0'};
					strcat(tmp[count], c);	
				}
				count++;
				POSX = 0;
				POSY = POSY + 1;
				if (POSY >= size_y())
				{
					POSY = POSY - 1;
					POSL = POSL + 1;
				}
			} 
			else if (bevor == 1)
			{
				tmp[count] = MSOCHARARR;
				tmp[count][0] = '\0';
				strcpy(tmp[count], "");
				count++;
				tmp[count] = MSOCHARARR;
				tmp[count][0] = '\0';
				strcpy(tmp[count], MAIN_FRAME.lines[i]);
				count++;
			}
			 else if (bevor == 2)
			{
				tmp[count] = MSOCHARARR;
				tmp[count][0] = '\0';
				strcpy(tmp[count], MAIN_FRAME.lines[i]);
				count++;
				tmp[count] = MSOCHARARR;
				tmp[count][0] = '\0';
				strcpy(tmp[count], "");
				count++;
				POSY = POSY + 1;
			}
		}
	}

	mem_free_char_array_array(MAIN_FRAME.lines, MAIN_FRAME.line_count);
	MAIN_FRAME.lines = malloc(sizeof(char*) * count);
	for (int i = 0;i < count;i++)
	{
		MAIN_FRAME.lines[i] = calloc((strlen(tmp[i]) + 1), sizeof(char));
		strcpy(MAIN_FRAME.lines[i], tmp[i]);
	}
	MAIN_FRAME.line_count = count;
	mem_free_char_array_array(tmp,count);
}

void save_window_file(void)
{
	set_was_edit(0);
	struct file_data *fd = create_file();
	for (int i = 0; i < MAIN_FRAME.line_count;i++)
		add_line_to_file(fd, MAIN_FRAME.lines[i]);
	write_file(get_file_arg(), fd);
	mem_free_file_data(fd);
}
