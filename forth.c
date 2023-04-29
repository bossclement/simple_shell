#include "main.h"

unsigned int is_delim(char c, char *delim);

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
	token = _strtok(str_cp, " ");
	while (token)
	{
		if (_strlen(str))
			_str_append(str, " %s", token);
		else
			_str_append(str, "%s", token);
		token = _strtok(NULL, " ");
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

/**
 * is_delim - function that check is string is delimeter
 * @c: character
 * @delim: delimeter
 * Return: number
 */

unsigned int is_delim(char c, char *delim)
{
	while (*delim != '\0')
	{
		if (c == *delim)
			return (1);
		delim++;
	}
	return (0);
}

/**
 * _strtok - function that works like strtok
 * @str: string to split
 * @delim: delimeter
 * Return: token
 */

char *_strtok(char *str, char *delim)
{
	static char *str_cp;
	char *picker;

	if (!str)
		str = str_cp;
	if (!str)
		return (NULL);
	while (1)
	{
		if (is_delim(*str, delim))
		{
			str++;
			continue;
		}
		if (*str == '\0')
			return (NULL);
		break;
	}
	picker = str;
	while (1)
	{
		if (*str == '\0')
		{
			str_cp = str;
			return (picker);
		}
		if (is_delim(*str, delim))
		{
			*str = '\0';
			str_cp = str + 1;
			return (picker);
		}
		str++;
	}
}
