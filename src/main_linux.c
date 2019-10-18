#include <nonamedef.h>
#include <signal.h>

extern int was_edit;

bool is_running = 0;

void sys_quit()
{
	is_running = 0;
	//file_write()
}

void sys_console_open()
{
	endwin();
	system(NORMAL_SHELL);
	start_window();
}

void close()
{
	if (!was_edit)
	{
		sys_quit();
		return;
	}
	signal(SIGINT, close);
}

int main(int argc, char** argv)
{
	signal(SIGINT, close);
	is_running = 1;
	init_arg(argc, argv);

	init_befor_var();

	if (!has_file_arg()) 
		return printf("Error You have to pass a file with -f \"filename\"\n") ? 1 : 1;

	Sys_folder_init();
	init_key();
	init_monitor();

	if (has_arg_or_short_arg("-v", "-verbose")) 
		printf("Version:%s\nLinux Version:%s\nArch:%s\nHome Dir:%s\n", LINE_VERSION, Sys_version(), Sys_arch(), Sys_main_folder());

	start_window();
	init_syntax();
	load_syntaxs();
	draw_window();
	init_var();

	while (is_running)
		key_listener();	

	quit_window();
	
	return 0;
}
