#ifndef SYNTAX_H
#define SYNTAX_H

enum COLOR
{
	BLACK = 0,
	RED = 1,
	GREEN = 2,
	YELLOW = 3,
	BLUE = 4,
	MAGENTA = 5,
	CYAN = 6,
	WHITE = 7,
	ORANGE = 8,
	FIREBRICK = 9,
};

struct syntax_token
{
	char* word;
	int first_color, second_color, pair;
};

struct syntax
{
	char* name;
	char* author;
	char* version;
	char* file_end;
	struct syntax_token *syntax_tokens; // Array
	int syntax_token_count;
};

void init_syntax();
void load_syntaxs();
void load_syntax(char* name);
struct syntax* get_arg_syntax_file();
struct syntax* get__syntax_file(char* file);
int get_syntax_color(char* color);
int has_syntax_file(char* file);
int has_arg_syntax_file();
void draw_char_array(char* c);


#endif
