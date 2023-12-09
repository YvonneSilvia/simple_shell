#include "shell.h"

/**
 * convert_number - converter function, a clone of itoa
 * @num: number
 * @base: base
 * @flags: arguments flags
 *
 * Return: string
 */
char *convert_number(long int, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '_';
	}
	array = flags & CONVERT_LOWERCASE ? "01234
