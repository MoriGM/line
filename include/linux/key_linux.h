#ifndef KEY_LINUX_H
#define KEY_LINUX_H

enum KEY_TYPE
{
	EDITOR = 1,
	HEXSHOW = 2,
};

struct KEY_MAP
{
	void (*function)(void);
	int key;
	enum KEY_TYPE type;
};

struct COMMAND_KEY
{
	void (*function)();
	int *command;
};

void init_key();
void add_key(enum KEY_TYPE type, int key, void (*func)(void));
int on_key(enum KEY_TYPE t, int key);
void add_command_key(void(*func)(), int *command);
int on_command_key(int key[], int len);
void key_listener();
int is_banned_key(int c);

#endif
