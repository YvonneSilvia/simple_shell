#include "shell.h"
/**
*custom_strncpy - copies a string
*@source: - the source string
@destination: - to where to copy string
@size: - string size
*Return: - returns destination string
*/
char *custom_strncpy(char *source, char *destination, int size)
{
	int s = 0, d;

	while (source[s] != '\0'&& s < size - 1)
	{
		destination[s] = source[s];
		s++;
	}
	if (s < size)
	{
		d = s;
		while (d < size)
		{
			destination[d] = '\0';
			d++;
		}
	}
	return (destination);
}
/**
*search_char - searches for a char in a string
*@str: - string to be parsed
*@c: - character to locate
*Return: - returns location of the character
*/
char *search_char(char *str, char c)
{
	for (; *str != c; str++)
	{
		if (*str == '\0')
			return (NULL);
	}
	return (str);
}
/**
*str_append - appends a string to another
*@str1: - param for first string
*@str2: - param for 2nd string
*@size: - sizeto be used
*Return: - returns a full string
*/
char *str_append(char *str1, char *str2, int size)
{
	while (*str1) /*move to the end of str1*/
		str1++;
	while (size-- && *str2) /*copy at most n characters from str2*/
		*str1++ = *str2++;
	*str1 = '\0';
	return (str1);
}
