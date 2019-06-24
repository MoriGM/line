#include <nonamedef.h>

struct syntax **syntaxs;
int syntax_count, pair_count;

void init_syntax(void)
{
	if (has_colormode())
	{
		syntaxs = malloc(sizeof(struct syntax) * 100);
		syntax_count = 0;
		pair_count = 1;
		init_pair(0, WHITE, BLACK);
		init_color(ORANGE, 900, 400, 0);
		init_color(FIREBRICK, 998, 144, 144);
	}
}

void load_syntaxs(void)
{
	struct dir_files df = Sys_list_files(Sys_main_syntax_folder());
	for (int i = 0;i < df.dir_count;i++)
	{	
		char* text;
		text = MSOCHARARR;
		text[0] = '\0';
		strcat(text, Sys_main_syntax_folder());
		strcat(text, "/");
		strcat(text, df.dir_lines[i]);
		if (Sys_is_file(text))
			load_syntax(text);
		free(text);
	}
}

void load_syntax(char* name)
{
	if (!has_colormode())
		return;

	struct syntax *syn = malloc(sizeof(struct syntax));
	syn->syntax_token_count = 0;
	struct file_data *data = read_file(name);
	
	if (data->file_len == 1)
	{
		free(syn);
		mem_free_file_data(data);
		return;
	}
		
	char** header_lines;
	header_lines = MSOCHARPARR;
	int header_count = 0;

	char** syntax_lines;
	syntax_lines = MSOCHARPARR;
	
	int syntax_len = 0;
	
	bool header = FALSE;
	for (int i = 0;i < data->file_len;i++)
	{
		if (!strcmp("}",data->file_text[i]))
			header = FALSE;
		if (header)
		{
			header_lines[header_count] = MSOCHARARR;
			header_lines[header_count][0] = '\0';
			strcpy(header_lines[header_count], data->file_text[i]);
			header_count++;
		}
		else
		{
			if (strcmp("}", data->file_text[i]) && strcmp("{", data->file_text[i]))
			{
				syntax_lines[syntax_len] = MSOCHARARR;
				syntax_lines[syntax_len][0] = '\0';
				strcpy(syntax_lines[syntax_len], data->file_text[i]);
				syntax_len++;
			}
		}
		if (!strcmp("{",data->file_text[i]))
			header = TRUE;
	}
	for (int i = 0;i < header_count;i++)
	{
		struct split_string ss = split_string(header_lines[i]," ");
		if (ss.line_count >= 2)
		{
			if (!strcmp(ss.lines[0], "name"))
			{
				syn->name = MSOCHARARR;
				syn->name[0] = '\0';
				char* cc = create_string_from_array(ss.lines, " ", ss.line_count, 1, ss.line_count);
				strcat(syn->name, cc);
				free(cc);
			}
			else if (!strcmp(ss.lines[0], "author"))
			{
				syn->author = MSOCHARARR;
				syn->author[0] = '\0';
				char* cc = create_string_from_array(ss.lines, " ", ss.line_count, 1, ss.line_count);
				strcat(syn->author, cc);
				free(cc);
			}
			else if (!strcmp(ss.lines[0], "version"))
			{
				syn->version = MSOCHARARR;
				syn->version[0] = '\0';
				char* cc = create_string_from_array(ss.lines, " ", ss.line_count, 1, ss.line_count);
				strcat(syn->version, cc);
				free(cc);
			}
			else if (!strcmp(ss.lines[0], "filetype"))
			{
				syn->file_end = MSOCHARARR;
				syn->file_end[0] = '\0';
				char* cc = create_string_from_array(ss.lines, " ", ss.line_count, 1, ss.line_count);
				strcat(syn->file_end, cc);
				mem_free_char_array(cc);
			}

		}
		mem_free_split_string(&ss);
	}

	syn->syntax_tokens = malloc(sizeof(struct syntax_token) * 1000);
	for (int i = 0;i < syntax_len;i++)
	{
		struct split_string sss = split_string(syntax_lines[i]," ");
		if (sss.line_count == 3)
		{
			int pos = syn->syntax_token_count;
			syn->syntax_tokens[pos].word = MSOCHARARR;
			syn->syntax_tokens[pos].word[0] = '\0';
			strcpy(syn->syntax_tokens[pos].word, sss.lines[0]);
			syn->syntax_tokens[pos].first_color = get_syntax_color(sss.lines[1]);
			syn->syntax_tokens[pos].second_color = get_syntax_color(sss.lines[2]);
			init_pair(pair_count, syn->syntax_tokens[pos].first_color, syn->syntax_tokens[pos].second_color);
			syn->syntax_tokens[pos].pair = pair_count;
			pair_count = pair_count + 1;
			syn->syntax_token_count = syn->syntax_token_count + 1;
		}
		mem_free_split_string(&sss);
	}
	
	syntaxs[syntax_count] = syn;
	syntax_count = syntax_count + 1;
	mem_free_char_array_array(syntax_lines, syntax_len);
	mem_free_char_array_array(header_lines, header_count);
	mem_free_file_data(data);
}

int get_syntax_color(char* color)
{
	if (!strcmp(color, "BLACK")) 		return BLACK;
	if (!strcmp(color, "RED")) 		return RED;
	if (!strcmp(color, "GREEN")) 		return GREEN;
	if (!strcmp(color, "YELLOW")) 		return YELLOW;
	if (!strcmp(color, "BLUE")) 		return BLUE;
	if (!strcmp(color, "MAGENTA")) 		return MAGENTA;
	if (!strcmp(color, "CYAN")) 		return CYAN;
	if (!strcmp(color, "WHITE")) 		return WHITE;
	if (!strcmp(color, "ORANGE")) 		return ORANGE;
	if (!strcmp(color, "FIREBRICK"))	return FIREBRICK;

	return 0;
}

struct syntax* get_syntax_file(char* file)
{
	for (int i = 0;i < syntax_count;i++)
		if (end_with(file, syntaxs[i]->file_end))
			return syntaxs[i];
	return NULL;
	
}

struct syntax* get_arg_syntax_file(void)
{
	if (!has_file_arg())
		return NULL;
	return get_syntax_file(get_file_arg());
}

int has_syntax_file(char* file)
{
	for (int i = 0;i < syntax_count;i++)
		if (end_with(file, syntaxs[i]->file_end))
			return 1;
	return 0;
}

int has_arg_syntax_file(void)
{
	if (!has_file_arg())
		return 0;
	return has_syntax_file(get_file_arg());
}

void color_char_array(char* c,int pair)
{
	attroff(COLOR_PAIR(0));
	attron(COLOR_PAIR(pair));
	printw("%s", c);
	attroff(COLOR_PAIR(pair));
	attron(COLOR_PAIR(0));

}

void draw_char_array(char* c)
{
	for (int i = 0;i < strlen(c);i++)
	{
		int has_drawn = FALSE;
		struct syntax* syn = get_arg_syntax_file();
		for (int s = 0;s < syn->syntax_token_count;s++)
		{
			struct syntax_token st = syn->syntax_tokens[s];
			if (contains_char_array(st.word, "..."))
			{
				struct split_string ss = split_string(st.word, "...");
				if (ss.line_count == 2 && !strcmp(ss.lines[1],"") && strlen(c) >= (strlen(ss.lines[0])))
					if (start_with(c, ss.lines[0]))
					{
						color_char_array(c, st.pair);
						printw("\n");
						mem_free_split_string(&ss);
						return;
					}
				mem_free_split_string(&ss);
			}
		}
		for (int s = 0;s < syn->syntax_token_count;s++)
		{
			struct syntax_token st = syn->syntax_tokens[s];
			if (!contains_char_array(st.word, "..."))
			{	if ((strlen(c) - i) >= strlen(st.word))
					if (equals_at_point(c, st.word, i, (i + strlen(st.word))))
					{
						char* cc = string_from_to(c, i, (i + strlen(st.word)));
						color_char_array(cc, st.pair);
						free(cc);
						i = (i + strlen(st.word)) - 1;
						has_drawn = TRUE;
						break;
					}
			}
			else
			{
				if ((strlen(c) - i) >= strlen(st.word))
				{
					struct split_string ss = split_string(st.word, "...");
					if (ss.line_count == 3 && strcmp(ss.lines[1], "") && contains_char_array(c, ss.lines[0]) && contains_char_array(c, ss.lines[2]))
					{
						has_drawn = TRUE;
						mem_free_split_string(&ss);
						break;
					}
					mem_free_split_string(&ss);
				}
			}
		}
		if (!has_drawn)
			printw("%c", c[i]);
	}
	printw("\n");
}
