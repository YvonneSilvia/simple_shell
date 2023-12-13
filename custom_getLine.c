#include "shell.h"
/**
*_get_input - gets input from the command line
*@info: - struct type param
*Return: - returns bytes read
*/
ssize_t _get_input(info_t *info)
{
	static size_t j = 0, len = 0;
	static char *buffer = NULL;
	ssize_t read = 0;
	char **buffer_ptr = &(info->arg);
	char *p = buffer + 1;

	_putchar(BUF_FLUSH);
	read = _input_buffer(info, &buffer, &len);
	if (read == -1)
		return (-1);
	if (len)
	{
		_check_chain(info, buffer, &j, j, len);
		while (j < len && !_is_chain(info, buffer, &j))
			j++;
		j += 1;
		if (j >= len)
		{
			j = len = 0;
			info->command_buffer_type = CMD_NORM;
		}
		*buffer_ptr = p;
		return (_string_len(p));
	}
	*buffer_ptr = buffer;
	return (read);
}
/**
*_read_buffer - reads from the buffer
*@info: - struct type param
*@buffer: - buffer
*@size: - size
*Return: - returns read buffer
*/
ssize_t _read_buffer(info_t *info, char *buffer, size_t *size)
{
	ssize_t read = 0;

	if (*size == 0)
	{
		read = read(info->readfd, buffer, BUFFER);
		if (read >= 0)
			*size = (size_t)read;
	}
	return (read);
}
/**
*_input_buffer - buffers chained with commands
*@info: - struct type param
*@buffer: - the buffer address
*@len: - length
*Return: - returns read
*/
ssize_t _input_buffer(info_t *info, char **buffer, size_t *len)
{
	ssize_t read = 0;

	if (*len == 0)
	{
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, sigintHandler);
		read = USE_GETLINE ? getline(buffer, len, stdin)
		:_getline(info, buffer, len);
		if (read > 0)
		{
			if ((*buffer)[read - 1] == '\n')
			{
				(*buffer)[read - 1] = '\0';
				read--;
			}
			info->linecount_flag = 1;
			remove_comments(*buffer);
			history_list(info, *buffer, info->histcount++);
			*len = read;
			if (_strchr(*buffer, ';'))
				info->command_buffer = buffer;
		}
	}
	return (read);
}
/**
*_getline - get input fro STDIN
*@info: - struct type param
*@ptr: - buffer pointer
*@length: - length of buffer
*Return: - returns string input
*/
int _getline(info_t *info, char **ptr, size_t length)
{
	static char buffer[BUFFER];
	static size_t j = 0, len = 0;
	char *p = NULL, *new_ptr = NULL, *c;
	size_t read = 0, st = 0;
	size_t cap = 0, k;

	p = *ptr;
	if (p && length)
		st = *length;
	if (j == len)
		j = len = 0;
	read = _read_buffer(info, buffer, &len);
	if (read == -1 || (read == 0 && len == 0))
		return (-1);
	c = _strchr(buffer + j, '\n');
	k = c ? 1 + (unsigned int)(c - buffer) : len;
	do
	{
		cap += BUFSIZ;
		new_ptr = _realloc(p, st, st ? st + cap : cap + 1)
		if (!new_ptr)
			return (p ? free(p), -1 : -1);
		if (st)
			_strncat(new_ptr, buffer + j, k - j);
		else
			custom_strcpy(new_ptr, buffer + j, k - j + 1);
		st += k - j;
		j = k;
		p = new_ptr;
		if (length)
			*length = st;
		*ptr = p;
	}
	while (!c);
	return(st);
}
/**
*sigintHandler - blocks any use of CTRL + C
*@siginum: - the signal number
*Return: - returns nothing
*/
void sigintHandler(__attribute__((unused))int siginum)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
