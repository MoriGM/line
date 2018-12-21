#ifndef NONAMEDEF_H
#define NONAMEDEF_H

//Linux Headers
#ifdef LINUX
#include <linux/window_linux.h>
#include <linux/sys_linux.h>
#include <ncurses.h>
#include <linux/key_linux.h>
#include <linux/monitor_linux.h>
#include <linux/sys_linux.h>
#endif
//End Linux Headers

#include <arg.h>
#include <sys_file.h>
#include <stringh.h>
#include <color.h>
#include <syntax.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <memfree.h>
#include <key_map.h>

#define NONAME_VERSION "0.0.1"
#define NONAME_NAME "line"
#define NONAME_CODER "MoriGM"
#define NONAME_MAIN_WINDOW_WIDTH 1200
#define NONAME_MAIN_WINDOW_HEIGHT 800
#define MSOCHAR malloc(sizeof(char))
#define MSOCHARARR malloc(sizeof(char) * 1000)
#define MSOINT malloc(sizeof(int))
#define MSOCHARPARR malloc(sizeof(char*) * 1000)

#ifndef add
#define add(x,y) x = x + y
#endif

#ifndef STRG
#define STRG(c) ((c) & 037)
#endif


//Main Functions

void sys_quit();
void sys_console_open();

void init_befor_var();
void init_var();

void set_was_edit(int i);

//End Main Fucntions

#endif
