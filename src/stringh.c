#include <nonamedef.h>

char* string_from_to(char* text,int start,int stop)
{
	char* tmp;
	tmp = MSOCHARARR;
	int x = 0;
	for (int i = (start > strlen(text) ? 0 : start); i < (stop > strlen(text) ? strlen(text) : stop);i++)
		tmp[x++] = text[i];
	tmp[x] = '\0';
	return tmp;
}

struct split_string split_string(char* text,char* split)
{
	struct split_string split_s;
	split_s.line_count = 0;
	split_s.lines = MSOCHARPARR;
	split_s.lines[0] = MSOCHARARR;
	split_s.lines[0][0] = '\0';
	for (int i = 0;i < strlen(text);i++)
		if (text[i] == split[0] && (strlen(text) - i) >= strlen(split))
		{
			char* _cc = string_from_to(text, i, (i + strlen(split)));
			if (!strcmp(_cc, split))
			{
				i += (strlen(split) - 1);
				add(split_s.line_count, 1);
				split_s.lines[split_s.line_count] = MSOCHARARR;
				split_s.lines[split_s.line_count][0] = '\0';
			}
			else
			{
				char* cc = create_char_array(text[i]);
				strcat(split_s.lines[split_s.line_count], cc);
				mem_free_char_array(cc);
			}
			mem_free_char_array(_cc);
		}
		else
		{
			char* cc = create_char_array(text[i]);
			strcat(split_s.lines[split_s.line_count], cc);
			mem_free_char_array(cc);
		}

	add(split_s.line_count, 1);

	return split_s;
}

char* create_char_array(char c)
{
	char* cc = malloc(sizeof(char) * 3);
	cc[0] = c;
	cc[1] = '\0';
	return cc;
}

int end_with(char* text,char* end)
{
	if (strlen(end) > strlen(text))
		return 0;
	if (!strcmp(text, end))
		return 1;
	
	for (int i = 0;i <= strlen(end);i++)
		if (text[strlen(text) - i] != end[strlen(end) - i])
			return 0;

	return 1;
}

char* create_string_from_array(char** c,char* add,int count,int start,int stop)
{
	char* tmp = MSOCHARARR;
	tmp[0] = '\0';
	for (int i = (start > count ? 0 : start);i < (stop > count ? count : stop);i++)
	{
		if (strlen(tmp) > 0)
			strcat(tmp, add);
		strcat(tmp,c[i]);
	}
	return tmp;
}

int equals_at_point(char* original,char* word,int start,int stop)
{
	char* cc = string_from_to(original, start, stop);
	int i = !strcmp(cc, word);
	mem_free_char_array(cc);
	return i;
}

int contains_char_array(char* text,char* word)
{
	for (int i = 0;i < strlen(text);i++)
		if ((strlen(text) - i) >= strlen(word))
			if (equals_at_point(text, word, i, (i + strlen(word))))
				return 1;

	return 0;
}

int start_with(char* text,char* start)
{
	if (strlen(start) > strlen(text))
		return 0;
	if (!strcmp(text, start))
		return 1;

	for (int i = 0;i < strlen(start);i++)
		if (text[i] != start[i])
			return 0;

	return 1;
}


void char_array_lower_case(char* cc)
{
	for (int i = 0;i < strlen(cc);i++)
		if (cc[i] >= 'A' && cc[i] <= 'Z')
			cc[i] = cc[i] - 'A' + 'a';
}

void char_array_upper_case(char* cc)
{
	for (int i = 0;i < strlen(cc);i++)
		if (cc[i] >= 'a' && cc[i] <= 'z')
			cc[i] = cc[i] - 'a' + 'A';
}
