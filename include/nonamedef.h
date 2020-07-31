#ifndef NONAMEDEF_H
#define NONAMEDEF_H

//Linux Headers
#ifdef LINUX
#define _XOPEN_SOURCE 500
#include <linux/window_linux.h>
#include <linux/sys_linux.h>
#include <ncurses.h>
#include <linux/key_linux.h>
#include <linux/monitor_linux.h>
#endif
//End Linux Headers

#include <stdio.h>
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
#include <transcode.h>
#include <hexshow.h>
#include <utils.h>

#define NONAME_CODER "MoriGM"
#define NORMAL_SHELL "bash"
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

void sys_quit(void);
void sys_console_open(void);

void init_befor_var(void);
void init_var(void);

void uninit_befor_var(void);

void set_was_edit(int i);

extern enum KEY_TYPE key_type;

//End Main Fucntions

#endif
