#include "shell.h"
/**
*history_file - handles files in history
*@info: - struct param
*Return: - returns a string with history file
*/
char *history_file(info_t *info)
{
	char *buffer, *directory;

	directory = _getenv(info, "HOME=");
	if (!directory)
		return (NULL);
	buffer = malloc(sizeof(char) * (_string_len(directory)
	+ _string_len(HIST_FILE) + 2));
	if (!buffer)
		return (NULL);
	buffer[0] = 0;
	_strncpy(buffer, directory);
	_strcat(buffer, "/");
	_strcat(buffer, HIST_FILE);
	return (buffer);
}
/**
*read_history - reads history of commands from a file
*@info: - struct type param
*Return: - returns a number of history nodes, or 0 on failure
*/
int read_history(info_t *info)
{
	int i, count = 0, last = 0;
	struct stat st;
	ssize_t fd, readlen, size = 0;
	char *buffer = NULL;
	char *file = history_file(info);

	if (!file || (fd = open(file, O_RDONLY)) == -1)
		return (0);
	free(file);
	if (!fstat(fd, &st) && (size = st.st_size) > 1)
	{
		buffer = malloc(size + 1);
		if (buffer && (readlen = read(fd, buffer, size)) > 0)
		{
			buffer[size] = '\0';
			for (i = 0; i < size; i++)
			{
				if (buffer[i] == '\n')
				{
					buffer[i] = '\0';
					history_list(info, buffer + last, count++);
					last = i + 1;
				}
			}
			if (last != i)
				history_list(info, buffer + last, count++);
			free(buffer);
		}
	}
	close(fd);
	info->histcount = count;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_someindex(&(info->history), 0);
	renumber_history(info);
	return (count);
}
/**
*renumber_history - remembers the command history
*@info: - struct type param
*Return: - returns history count
*/
int renumber_history(info_t *info)
{
	list_t* node = info->history;
	int j = 0;

	while (node)
	{
		node->num = j++;
		node = node->next;
	}
	return (info->histcount = j);
}
/**
*write_into_history - writes history of commands from a
*linked list history
*@info: - struct type param
*Return:- returns 1 on success and -1 on failure
*/
int write_history(info_t *info)
{
	char *file = history_file(info);
	int fd;
	list_t *node = NULL;

	if (!file)
		return (-1);
	fd = open(file, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(file);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}
/**
*history_list - adds commands to history list
*@info: - struct type param
*@linecount: - number of lines
*@buffer: - access to the buffer
*Return: - returns 0 success
*/
int history_list(info_t *info, char *buffer, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_at_end(&node, buffer, linecount);
	if (!info->history)
		info->history = node;
	return (0);
}
