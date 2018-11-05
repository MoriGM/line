#ifndef NONAMEDEF_H
#define NONAMEDEF_H

//Linux Headers
#ifdef LINUX
#include "window_linux.h"
#include "sys_linux.h"
#include <ncurses.h>
#include "key_linux.h"
#include "monitor_linux.h"
#include "sys_linux.h"
#endif
//End Linux Headers

#include "arg.h"
#include "sys_file.h"
#include "stringh.h"
#include "color.h"
#include "syntax.h"
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "memfree.h"

#define NONAME_VERSION "0.0.0"
#define NONAME_NAME "Line"
#define NONAME_CODER "MoriGM"
#define NONAME_MAIN_WINDOW_WIDTH 1200
#define NONAME_MAIN_WINDOW_HEIGHT 800
#define MSOCHAR malloc(sizeof(char))
#define MSOCHARARR malloc(sizeof(char) * 1000)
#define MSOINT malloc(sizeof(int))

#ifndef add
#define add(x,y) x = x + y
#endif

#ifndef STRG
#define STRG(c) ((c) & 037)
#endif


//Main Functions

void sys_quit();

//End Main Fucntions

#endif
