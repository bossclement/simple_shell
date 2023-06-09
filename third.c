#include "main.h"

/**
 * int_to_str - function to change a number to string
 * @num: the number to change
 * @dest: pointer to a string where to store my number
 * Return: pointer to a character
 */

char *int_to_str(long int num, char *dest)
{
	int remainder, index = 0;
	char str_num[STRLEN];

	while (num != 0)
	{
		remainder = num % 10;
		num /= 10;
		str_num[index] = (char)(remainder + '0');
		index++;
	}

	remainder = 0;
	while (index--)
	{
		dest[remainder] = str_num[index];
		remainder++;
	}

	dest[remainder] = '\0';

	return (dest);
}

/**
 * sigint_handler - function that handle signals
 * @sig: signal received
 */

void sigint_handler(int sig)
{
	_write(STDOUT_FILENO, "\n~$ ", &sig, "./hsh");
}

/**
 * string_append - function that appends strings
 * @dest: where to copy strings
 * @org: string to copy from
 */

void string_append(char *dest, char *org)
{
	int count = 0;

	if (org != NULL && dest != NULL)
	{
		while (org[count])
		{
			dest[_strlen(dest)] = org[count];
			count++;
		}
	}
}

/**
 * program_checker - function that appends strings
 * @program_path: absolute path of the command
 * @argv: arguments passed in the program
 * @args: command line arguments
 * @info: information about my shell
 * Return: number
 */

int program_checker(char *program_path, char **argv, char **args, INFO *info)
{
	struct stat st;

	if (!is_path(program_path)) /* not found */
	{
		_clear_str(program_path);
		print_error(argv[0], args[0], "not found", 127, info);
		return (0);
	} else if ((stat(program_path, &st) == 0 &&
	S_ISDIR(st.st_mode)) || access(program_path, X_OK) != 0)
	{
		_clear_str(program_path);
		print_error(argv[0], args[0], "Permission denied", 126, info);
		return (0);
	}
	return (1);
}

/**
 * _getenv - gets an environment variable
 * @envir: absolute path of the command
 * @envirs: file permission errors
 * @dest: arguments passed in the program
 */

void _getenv(char *envir, char **envirs, char *dest)
{
	int envir_len = _strlen(envir), p = 0, c, i = 0;

	if (envirs == NULL || dest == NULL)
		return;
	while (envirs[p])
	{
		for (c = 0; c < envir_len; c++)
		{
			if (envirs[p][c] != envir[c])
				break;
		}
		if (c == envir_len)
			break;
		p++;
	}
	if (envirs[p] == NULL)
		return;
	while (envirs[p][c])
	{
		dest[i] = envirs[p][c];
		i++;
		c++;
	}
}
