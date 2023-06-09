#include "main.h"

/**
 * _write - function that writes data on console
 * @fd: file descriptor
 * @buffer: where to store command line
 * @status: checks if my shell should run
 * @fname: program name
 */

void _write(int fd, char *buffer, int *status, char *fname)
{
	size_t bytes_write;

	bytes_write = write(fd, buffer, _strlen(buffer));
	if (bytes_write != _strlen(buffer))
		error(1, status, fname);
}

/**
 * _free - function that frees allocated memory
 * @array: array to free
 * @str: string to free
 */

void _free(void **array, void *str)
{
	int index = 0;

	if (str != NULL)
	{
		free(str);
	}

	if (array != NULL)
	{
		while (array[index])
		{
			free(array[index]);
			index++;
		}
	}
}

/**
 * execute_cmd - function that executes command
 * @args: file descriptor
 * @environs: environment variables
 * @status: checks if my shell should run
 * @info: program information
 */

void execute_cmd(char **args, char **environs, int *status, INFO *info)
{
	pid_t pid;
	int exec_status;

	pid = fork();
	if (pid < 0)
		error(1, status, info->fname);
	else if (pid == 0)
	{
		execve(args[0], args, environs);
	}
	else
	{
		waitpid(pid, &exec_status, 0);
	}
	switch (exec_status) /* enterpret exit codes */
	{
		case 512:
			info->exit_code = 2;
			break;

		default:
			info->exit_code = 0;
			break;
	}
}

/**
 * _clear_str - function that clears data in string
 * @str: the string to clear
 */

void _clear_str(char *str)
{
	int i = 0;

	while (str && str[i])
	{
		str[i] = '\0';
		i++;
	}
}

/**
 * free_my_vars - function that frees all allocated memory in
 *		my program
 * @program_path: absolute path of the program
 * @user_input: input from the user
 * @path: PATH environment variable
 * @info: program information
 */

void free_my_vars(char *program_path, char *user_input, char *path, INFO *info)
{
	_free((void **)info->envp, user_input);
	_free(NULL, path);
	_free(NULL, program_path);
	_free(NULL, info);
}
