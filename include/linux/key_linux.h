#ifndef KEY_LINUX_H
#define KEY_LINUX_H

enum KEY_TYPE
{
	EDITOR = 1,
	HEXSHOW = 2,
};

struct KEY_MAP
{
	int (*function)(int);
	enum KEY_TYPE type;
};

struct COMMAND_KEY
{
	int (*function)(int[], int);
};

void init_key();
void add_key(enum KEY_TYPE type, int (*func)(int));
int on_key(enum KEY_TYPE t, int key);
void add_command_key(int(*func)(int[], int));
int on_command_key(int key[], int len);
void key_listener();
int is_banned_key(int c);

#endif
