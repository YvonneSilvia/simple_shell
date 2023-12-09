#include "shell.h"
/**
*_strdup - allocates a new memory
*@str: - a string to copy to the memory
*Return: - pointer to the string in memory
*/
char *_strdup(const char *str)
{
	char *ret = malloc(_string_len(str) + 1);

	if (str == NULL)
		return (NULL);
	if (ret == NULL)
		return (NULL);
	_custom_strncpy(ret, str);
	return (ret);
}
/**
*_puts - prints an output string
*@str: - string to output
*Return: - returns nothing
*/
void _puts(char *str)
{
	if (str)
	{
		for (; *str; str++)
			_putchar(*str);
	}
}
/**
*_putchar - writes character c to the buffer
*@c: - character to be written
*Return: - 1 on success
*/
int _putchar(char c)
{
	static char buffer[WRITE_BUF_SIZE];
	static int i = 0;

	if (c == BUF_FLUSH || i == WRITE_BUF_SIZE)
	{
		write(1, buffer, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
	{
		buffer[i] = c;
		i++;
	}
	return (1);
}
