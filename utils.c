#include "main.h"

/**
 * _strcp - function that copies a string
 * @str: string to copy
 * @dest: destination where to copy the string
 */

void _strcp(char *str, char *dest)
{
	size_t index = 0;

	while (str[index])
	{
		dest[index] = str[index];
		index++;
	}
	dest[index] = '\0';
}

/**
 * _strlen - function that gets a string length
 * @str: string to get the length for
 * Return: size of the string
 */

size_t _strlen(char *str)
{
	size_t length = 0;

	if (str == NULL)
		return (0);
	while (str[length])
		length++;
	return (length);
}

/**
 * allocate - function that allocates memory in the heap
 * @size: size of the memory to allocate
 * @status: my program run status
 * @fname: program name
 * Return: pointer to the memory allocated
 */

char *allocate(ssize_t size, int *status, char *fname)
{
	char *pt;
	ssize_t index;

	pt = (char *) malloc(size);
	if (pt != NULL)
	{
		for (index = 0; index < (ssize_t)(size / sizeof(char)); index++)
			pt[index] = '\0';
		return (pt);
	}
	else
		error(1, status, fname);
	return (NULL);
}

/**
 * _strcmp - function that compares strings
 * @org: orginal string
 * @cp: string to compare with
 * Return: 1 if they match 0 otherwise
 */

int _strcmp(char *org, char *cp)
{
	int len_org, len_cp;

	len_org = _strlen(org);
	len_cp = _strlen(cp);

	if (len_cp != len_org)
		return (0);
	while (len_org)
	{
		if (org[len_org] != cp[len_org])
			return (0);
		len_org--;
	}
	return (1);
}

/**
 * error - function that prints error to standard error output
 * @ex: check if program should be terminated
 * @status: my program run status
 * @fname: program name
 */

void error(int ex, int *status, char *fname)
{
	perror(fname);
	if (ex)
		*status = 0;
}
