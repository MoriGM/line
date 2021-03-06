#include <nonamedef.h>
#include <sys/utsname.h>
#include <pwd.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>

void Sys_folder_init(void)
{
	if (!Sys_exists_folder(Sys_main_folder()))
		Sys_mkdir(Sys_main_folder());
	if (!Sys_exists_folder(Sys_main_syntax_folder()))
		Sys_mkdir(Sys_main_syntax_folder());
}


char* Sys_version(void)
{
	struct utsname utsn;

	uname(&utsn);

	char* cc = malloc(sizeof(char) * (strlen(utsn.release) + 1));
	
	strcpy(cc,utsn.release);
	
	return cc;
}

char* Sys_arch(void)
{
	struct utsname utsn;

	uname(&utsn);

	char* cc = malloc(sizeof(char) * (strlen(utsn.machine) + 1));

	strcpy(cc,utsn.machine);
	
	return cc;

}

struct dir_files Sys_list_files(char* c)
{
	DIR *d;
	struct dirent *dir;
	struct dir_files df;
	df.dir_count = 0;
	df.dir_lines = MSOCHARARR;
	
	d = opendir(c);
	
	if (d)
	{
		while((dir = readdir(d)) != NULL)
		{
			if (!strcmp(dir->d_name, ".") || !strcmp(dir->d_name, ".."))
				continue;
			df.dir_lines[df.dir_count] = MSOCHARARR;
			df.dir_lines[df.dir_count][0] = '\0';
			strcpy(df.dir_lines[df.dir_count],dir->d_name);
			df.dir_count = df.dir_count + 1;
		}
		closedir(d);
	}
	
	free(dir);
	
	return df;
}

int Sys_is_folder(char* c)
{
	struct stat st;
	if (stat(c,&st) == -1)
		return 0;
	return S_ISDIR(st.st_mode);
}

int Sys_is_file(char* c)
{
	struct stat st;
	if (stat(c,&st) == -1)
		return 0;
	return S_ISREG(st.st_mode);
}

int Sys_exists_folder(char* c)
{
	struct stat st;
	if (stat(c,&st) == -1)
		return 0;
	else
		return 1;
}

int Sys_mkdir(char* c)
{
	return mkdir(c,0777);
}

char* Sys_main_folder(void)
{
	struct passwd *pw = getpwuid(getuid());
	
	char* homedir = pw->pw_dir;

	strcat(homedir, "/.");

	strcat(homedir, LINE_NAME);

	strcat(homedir, "/");
	
	return homedir;
}

char* Sys_main_syntax_folder(void)
{
	char* homedir = Sys_main_folder();

	strcat(homedir, "syntax");
	
	return homedir;
}
