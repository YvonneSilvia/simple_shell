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
		flush_info(info);
		if (is_interactive(info))
			custom_puts("$ ");
		_eputchar(FLUSH_BUFFER);
		t = _input(info);
		if (t != -1)
		{
			setInfo(info, argv);
			sys_builtin = builtin_search(info);
			if (sys_builtin == -1)
				find_command(info);
		}
		else if (is_interactive(info))
			_putchar('\n');
			free_info(info, 0);
	}
	record_history(info);
	free_info(info, 1);
	if (!is_interactive(info) && info->status)
		exit(info->status);
		if (sys_builtin == -2)
		{
			if (info->err == -1)
				exit(info->status);
			exit(info->err);
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
		{"exit", _custom_exit},
		{"env", custom_env},
		{"help", custom_help},
		{"history", custom_history},
		{"setenv", custom_setenv},
		{"unsetenv", custom_unsetenv},
		{"cd", custom_cd},
		{"alias", custom_alias},
		{NULL, NULL}
	};

	for (i = 0; builtintable[i].type; i++)
		if (_strcmp(info->argv[0], builtintable[i].type) == 0)
		{
			info->line_count++;
			sys_builtin = builtintable[i].func(info);
			break;
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
		if (execve(info->path->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == AACCES)
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
	char sys_path = NULL;

	info->path = info->argv[0];
	if (info->count_flag == 1)
	{
		info->count++;
		info->count_flag = 0;
	}
	for (i = 0, j = 0; info->argv[i]; i++)
		if (!is_delimeter(info->argv[i], " \t\n"))
			j++;
	if (!j)
		return;
	sys_path = get_path(info, sys_getenv(info, "PATH="), info->argv[0]);
	if (sys_path)
	{
		info->path = sys_path;
		command_fork(info);
	}
	else
	{
		if ((is_interactive(info) || sys_getenv(info, "PATH=")
			|| info->argv[0][0] == '/') && is_command(info->argv[0]))
			command_fork(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}
