#include "shell.h"
/**
*loop_shell - shell's main execute loop
*@info: - struct param
*@argv: - an argument vector
*Return: - return 0 on success and 1 on failure
*/
int loop_shell(info_t *info, char **argv)
{
	ssize_t t;
	int sys_builtin = 0;

	while (t != -1 && sys_builtin != -2)
	{
		_flush_info(info);
		if (is_interactive(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		t = _get_input(info);
		if (t != -1)
		{
			_set_info(info, argv);
			sys_builtin = builtin_search(info);
			if (sys_builtin == -1)
				get_command(info);
		}
		else if (is_interactive(info))
			_putchar('\n');
		_free_info(info, 0);
	}
	write_history(info);
	_free_info(info, 1);
	if (!is_interactive(info) && info->status)
		exit(info->status);
	if (sys_builtin == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (sys_builtin);
}
/**
*builtin_search - searches for any matching builtin command
*@info: - the struct type param
*Return: - returns 0 for success, 1 for unsuccess, -1 for not found
* and -2 for exit
*/
int builtin_search(info_t *info)
{
	int i, sys_builtin = -1;
	builtin_table builtintable[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (i = 0; builtintable[i].type; i++)
	{
		if (_strcmp(info->argv[0], builtintable[i].type) == 0)
		{
			info->line_count++;
			sys_builtin = builtintable[i].func(info);
			break;
		}
	}
	return (sys_builtin);
}
/**
*command_fork - forks exec to to run the command
*@info: - struct type param
*Return: - returns nothing
*/
void command_fork(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			_free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}
/**
*get_command - gets the command path
*@info: - struct parameter type
*Return: - returns nothing
*/
void get_command(info_t *info)
{
	int i, j;
	char *path = NULL;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, j = 0; info->argv[i]; i++)
		if (!is_delimeter(info->arg[i], " \t\n"))
			j++;
	if (!j)
		return;
	path = get_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		command_fork(info);
	}
	else
	{
		if ((is_interactive(info) || _getenv(info, "PATH=")
			|| info->argv[0][0] == '/') && is_command(info, info->argv[0]))
			command_fork(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}
