#ifndef STRINGH_H
#define STRINGH_H

struct split_string
{
	char** lines;
	int line_count;
};

char* string_from_to(char* text,int start,int stop);
struct split_string split_string(char* text,char* split);
char* create_char_array(char c);
char* create_string_from_array(char** c,char* add,int count,int start,int stop);
int end_with(char* text,char* end);
int equals_at_point(char* original,char* word,int start,int stop);
int contains_char_array(char* text,char* word);
int start_with(char* text,char* start);

#endif
