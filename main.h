#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <dirent.h>
#include <errno.h>
#include <stdarg.h>
#include <sys/stat.h>
#include <signal.h>
#include <sys/types.h>

/**
 * struct APP_INFO - stores information
 * @wd: working directory
 * @fname: program name
 * @envp: environment variables
 * @argc: number of arguments passed in the program
*/

struct APP_INFO
{
	char wd[1024];
	char *fname;
	char *envp[100];
	int argc;
};
typedef struct APP_INFO INFO;

extern char **environ;

void _strcp(char *str, char *dest);
char *allocate(ssize_t size, int *status, char *fname);
void error(int ex, int *status, char *fname);
size_t _strlen(char *str);
int _strcmp(char *org, char *cp);
void _str_append(char *result, char *format, ...);
void cp_environ(char **dest, char **from);
void find_path(char *program_name,
char *program_path, char *dir, int *status, char *fname);
void _clear_str(char *str);
void cp_commands(char **argv, char *dest);
void get_arguments(char **args, char *cmd);
void _write(int fd, char *buffer, int *status, char *fname);
void _free(void **array, void *str);
void free_my_vars(char *program_path,
char *user_input, char *path, INFO *info);
void execute_cmd(char **args, char **environs, int *status, char *fname);
char *int_to_str(long int num, char *dest);
void sigint_handler(int sig);
void string_append(char *dest, char *org);
int program_checker(char *program_path, int *error_counts,
char **argv, int *status, char **args, INFO *info);
void _getenv(char *envir, char **envirs, char *dest);
size_t check_input(char *str);

#endif
