#include "shell.h"
/**
*locate_executable - locates commands
*@info: - struct type param
*@path: - defined path of command
*@command: - command type
*Return: - returns the path of command
*/
char *locate_executable(info_t info, char *path, char command)
{
	int i, curr_pos;
	char *p;

	if (!path)
		return (NULL);
	if ((_string_len(command) > 2) && begin_with(command, "./")
		&& is_command(info, command))
		return (command);
	for (i = 0, curr_pos = 0; path[i] != '\0'; i++)
	{
		if (path[i] == ':')
		{
			p = duplicate_chars(path, curr_pos, i);
			_strcat(p, (*p ? "/" : ""), command);
			if (is_command(info, p))
				return (p);
			curr_pos = i + 1;
		}
	}
	return (NULL);
}
/**
*is_command - checks if it's a command
*@info: - struct type param
*@path: - location of the command
*@Return: - returns 1 success and 0 otherwise
*/
int is_command(info_t *info, char *path)
{
	(void)info;

	if (!path || access(path, X_OK))
		return (0);
	return (1);
}
/**
*duplicate_chars - duplicates characters
*@path - the string path
*@start: - the beginning index
*@end: - the ending index
*Return: - returns pointer to new block
*/
char *duplicate_chars(char *path, int start, int end)
{
	int len = end - start;
	static char buffer[1024];

	custom_strcpy(buffer, path + start, len);
	buffer[len] = '\0';
	return (buffer);
}
