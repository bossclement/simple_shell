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

typedef struct
{
	char wd[1024];
	char *fname;
	char *envp[100];
} INFO;
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
void _print(char **args);

#endif
