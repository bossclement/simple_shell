#include "main.h"

/**
 * check_input - function that check command
 * @str: command
 * Return: number
 */

size_t check_input(char *str)
{
	char str_cp[STRLEN], *token;

	_strcp(str, str_cp);
	_clear_str(str);
	token = strtok(str_cp, " ");
	while (token)
	{
		if (_strlen(str))
			_str_append(str, " %s", token);
		else
			_str_append(str, "%s", token);
		token = strtok(NULL, " ");
	}
	return (_strlen(str) - 1);
}

/**
 * is_path - check if a string is a path and exists
 * @str: path
 * Return: number
 */

int is_path(char *str)
{
	int index = 0;

	if (str == NULL)
		return (0);

	while (str[index])
	{
		if (str[index] == '/' && access(str, F_OK) == 0)
			return (1);
		index++;
	}
	return (0);
}
