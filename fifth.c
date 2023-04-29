#include "main.h"

/**
 * print_error - function that check command
 * @fname: program name
 * @cmd: executable
 * @msg: error message
 * @exit_code: program exit code
 * @info: program information
 * Return: number
 */

void print_error(char *fname, char *cmd, char *msg, int exit_code, INFO *info)
{
	static int error_counts = 1;
	char message[STRLEN];
	size_t bytes_write;
	int x = 0;

	for (x = 0; x < STRLEN; x++)
		message[x] = '\0';

	_str_append(message, "%s: %d: %s: %s\n", fname, error_counts, cmd, msg);
	error_counts++;
	info->exit_code = exit_code;
	bytes_write = write(STDERR_FILENO, message, _strlen(message));
	if (bytes_write != _strlen(message))
	{
		perror("write");
		exit(0);
	}
}

/**
 * get_exit_code - gets program exit code
 * @str: number
 * @info: program information
 */

void get_exit_code(char *str, INFO *info)
{
	int num = 0, i = 0, x;
	char msg[STRLEN];
	
	for (x = 0; x < STRLEN; x++)
		msg[x] = '\0';

	if (str == NULL)
	{
		info->exit_code = 0;
		return;
	}
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
		{
			_str_append(msg, "%s: %s", "Illegal number", str);
			print_error(info->fname, "exit", msg, 2, info);
			return;
		}
		num = num * 10 + (str[0] - '0');
		i++;
	}
	num--;
	if (num > 232)
	{
		num = 232;
	}
	info->exit_code = num;
}

/**
 * check_built_in - checks built in functions
 * @args: commandline arguments
 * @info: program information
 * @status: program running status
 * Return: number
 */

int check_built_in(char **args, INFO *info, int *status)
{
	if (_strcmp(args[0], "exit"))
	{
		get_exit_code(args[1], info);
		*status = 0;
		return (1);
	}

	return (0);
}
