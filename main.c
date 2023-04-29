#include "main.h"

#define MAX_ARGS 100

void program_path_finder(char **args, char *user_input,
char *path, char *program_path);
void prepare_data(char *fname, int *status, INFO *info, int argc);
void get_input(char *buffer, int *status, INFO *info);

/**
 * get_input - function that gets input from a user
 * @buffer: where to store command line
 * @status: my program run status
 * @info: program information
 */

void get_input(char *buffer, int *status, INFO *info)
{
	int i = 0;
	ssize_t read;

	if (isatty(STDIN_FILENO))
	{
		_write(STDOUT_FILENO, "~$ ", status, info->fname);
	}
	fflush(stdout);
	_clear_str(buffer);
	read = _getline(buffer, status);
	if (read <= 0)
	{
		if (isatty(STDIN_FILENO))
			_write(STDOUT_FILENO, "\n", status, info->fname);
		_clear_str(buffer);
	}

	if (*status == 0)
		_strcp("exit", buffer);

	if (!_strcmp("\n", buffer))
	{
		while (buffer[i]) /* Remove new line */
		{
			if (buffer[i] == '\n')
				buffer[i] = '\0';
			i++;
		}
		buffer[_strlen(buffer)] = '\0';
	}

	if (_strcmp("\n", buffer))
		_clear_str(buffer);
}

/**
 * prepare_data - function that prepares everything the program will need
 * @fname: the program name
 * @status: my program run status
 * @info: my program information
 * @argc: number of arguments passed in the program
 */

void prepare_data(char *fname, int *status, INFO *info, int argc)
{
	int index = 0;

	/* Set my App information */
	while (environ[index]) /* allocates memory for my environment variables */
	{
		info->envp[index] = allocate(_strlen(environ[index]) + 1, status, fname);
		_strcp(environ[index], info->envp[index]);
		index++;
	}
	info->envp[index] = NULL;
	info->fname = fname;
	getcwd(info->wd, sizeof(info->wd));
	if (info->wd == NULL)
		error(1, status, info->fname);
	info->argc = argc;
	info->exit_code = 0;
	cp_environ(info->envp, environ);
}

/**
 * program_path_finder - function that finds executable
 * @args: command line arguments
 * @user_input: command line from the user
 * @path: the PATH environment variable
 * @program_path: the absolute path of the program found
 */

void program_path_finder(char **args, char *user_input,
char *path, char *program_path)
{
	char *token;

	get_arguments(args, user_input);
	_getenv("PATH=", environ, path);
	token = _strtok(path, ":");
	_clear_str(program_path);
	while (token != NULL && program_path[0] == '\0')
	{
		find_path(args[0], program_path, token);
		token = _strtok(NULL, ":");
	}
	if (program_path[0] == '\0')
		_strcp(args[0], program_path);
}

/**
 * shell - where everything takes place
 * @status: checks if the shell is running
 * @argc: number of arguments passed in the program
 * @user_input: stores inputs from user
 * @info: structure containing stuffs i'll use
 * @argv: arguments passed in the program
 * @args: arguments from the command line
 * @path: PATH environment variable
 * @program_path: absolute path of the command passed
 * Return: exit status
 */

void shell(int status, int argc, char *user_input,
INFO *info, char **argv, char **args, char *path, char *program_path)
{
	signal(SIGINT, sigint_handler);
	while (status)
	{
		if (argc == 1)
		{
			_clear_str(user_input);
			get_input(user_input, &status, info);
		}
		else
		{
			status = 0;
			cp_commands(argv, user_input);
		}
		if ((user_input[0] == '\0' && !isatty(STDIN_FILENO)) || !status)
			continue;
		else if (user_input[0] == '\0' && isatty(STDIN_FILENO))
			continue;
		info->exit_code = 0;
		program_path_finder(args, user_input, path, program_path);
		if (check_built_in(args, info, &status))
			continue;
		if (!program_checker(program_path, argv, args, info))
			continue;
		args[0] = program_path;
		execute_cmd(args, info->envp, &status, info); /* execute program */
		_clear_str(program_path);
	}
}

/**
 * main - the main function
 * @argc: number of arguments passed in the program
 * @argv: command line passed in my shell
 * Return: exit status
 */

int main(int argc, char **argv)
{
	char *user_input, *args[MAX_ARGS], *program_path, *path;
	int status = 1, exit_code;
	INFO *info = (INFO *) malloc(sizeof(INFO));

	if (info == NULL)
	{
		perror(argv[0]);
		exit(0);
	}

	prepare_data(argv[0], &status, info, argc);
	user_input = allocate(STRLEN * sizeof(char), &status, info->fname);
	program_path = allocate(STRLEN * sizeof(char), &status, info->fname);
	path = allocate(STRLEN * sizeof(char), &status, info->fname);
	shell(status, argc, user_input, info, argv, args, path, program_path);
	exit_code = info->exit_code;
	free_my_vars(program_path, user_input, path, info);
	return (exit_code);
}
