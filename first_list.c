#include "main.h"

/**
 * _str_append - function that appends string
 * @result: place to store result of the appended strings
 * @format: the way string should be appended
 * @...: the restrings to append
 */

void _str_append(char *result, char *format, ...)
{
char *str, number[STRLEN];
va_list args;
int index = 0;

va_start(args, format);
while (format[index] && result != NULL)
{
	if (format[index] == '%')
	{
		switch (format[index + 1])
		{
			case 's':
				str = va_arg(args, char *);
				string_append(result, str);
				index++;
				break;
			case 'd':
				int_to_str(va_arg(args, int), number);
				string_append(result, number);
				index++;
				break;
			default:
				break;
		}
	} else
		result[_strlen(result)] = format[index];
	index++;
}
va_end(args);
}

/**
 * cp_environ - function that copy environment variables
 * @dest: destination
 * @from: where to copy from
 */

void cp_environ(char **dest, char **from)
{
	int i = 0;

	while (from[i])
	{
		_strcp(from[i], dest[i]);
		i++;
	}
	dest[i] = NULL;
}

/**
 * find_path - function that find executables in PATH variable
 * @program_name: the program to find
 * @program_path: the absolute path of the program
 * @dir: directory where to look for the program
 */

void find_path(char *program_name, char *program_path,
char *dir)
{
	DIR *dirp;
	struct dirent *dp;

	if (program_name == NULL || program_name[0] == '\0')
		return;
	else if (program_name[0] == '/' ||
	(program_name[0] == '.' && program_name[1] == '/'))
		_strcp(program_name, program_path);

	dirp = opendir(dir);
	if (dirp == NULL)
		return;

	while ((dp = readdir(dirp)) != NULL)
	{
		if (_strcmp(dp->d_name, program_name))
		{
			_str_append(program_path, "%s/%s", dir, program_name);
			break;
		}
	}

	closedir(dirp);
}

/**
 * cp_commands - function that copies arguments to a string
 * @argv: the arguments passed in the program
 * @dest: the string where to put the arguments
 */

void cp_commands(char **argv, char *dest)
{
	int i = 1;

	while (argv[i] != NULL)
	{
		_str_append(dest, "%s", argv[i]);
		i++;
	}
}

/**
 * get_arguments - function that places command arguments
 *		line to an array of strings
 * @args: array of arguments
 * @cmd: command line from user
 */

void get_arguments(char **args, char *cmd)
{
	char *substr;
	int i = 0;

	substr = _strtok(cmd, " ");
	while (substr != NULL)
	{
		args[i] = substr;
		substr = _strtok(NULL, " ");
		i++;
	}
	args[i] = NULL;
}
