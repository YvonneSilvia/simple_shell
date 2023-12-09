#include "shell.h"
/**
*_string_len - finds length of a string
*@str: - string param
*Return: - returns the length
*/
int _string_len(char *str)
{
	int len = 0;

	if (str)
	{
		while (str[len])
			len++;
	}
	return (len);
}
/**
*_strcat - concatenates strings
*@str1: first string
*@str2: - second string
*Return: - returns concatenated string str1
*/
char *_strcat(char *str1, char *str2)
{
	char *s = str1 + _string_len(str1);
	custom_strncpy(s, str2);
	return (str1);
}
/**
*begin_with - whether str1 begin with str2
*@str1: - string to search
*@str2: - string to find
*Return: - returns address to str1 or null
*/
char *begin_with(const char *str1, const char *str2)
{
	for (; *str2; str++, str1++)
	{
		if (*str2 != *str1)
			return (NULL);
	}
	return ((char *)str1);
}
/**
*_strcmp - compares two strings
*@str1: - first string param
*@str2: - second string param
*Return: - returns 1 or 0
*/
int _strcmp(char *str1, char *str2)
{
	while (*str1 && *str2 == *str2)
	{
		str1++;
		str2++;
	}
	return (((unsigned char)*str1) - ((unsigned int)*str2));
}
