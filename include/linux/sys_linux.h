#ifndef SYS_LINUX_H
#define SYS_LINUX_H

struct dir_files
{
	char** dir_lines;
	int dir_count;
};

void Sys_folder_init();
char* Sys_version();
char* Sys_arch();
struct dir_files Sys_list_files(char* c);
int Sys_is_folder(char* c);
int Sys_is_file(char* c);
int Sys_exists_folder(char* c);
int Sys_mkdir(char* c);
char* Sys_main_syntax_folder();
char* Sys_main_folder();

#endif
