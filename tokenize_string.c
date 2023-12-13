#include "shell.h"
/**
*_strwd1 - splits a string to word with si_delimeter
*@str: - string to be split
*@del: argument is_delimeter takes in call
*Return: - returns a pointer to array of words
*/
char **_strwd1(char * str, char *del)
{
	int l, m , p = 0, n = 0;
	char **s;

	if (!str || !*str)
		return (NULL);
	if (!del)
		del = " ";
	for (l = 0; str[l]; l++)
	{
		if (!is_delimeter(str[l], del) && (is_delimeter(str[l + 1],
			del) || !str[l + 1]))
			n++;
	}
	if (!n)
		return (NULL);
	s = malloc((n + 1) * sizeof(char *));
	if (!s)
		return (NULL);
	for (l = 0, m = 0; m < n; m++)
	{
		while (is_delimeter(str[l], del))
			l++;
		while (!is_delimeter(str[l + p], del) && str[l + p])
			p++;
		s[m] = malloc((p + 1) * sizeof(char));
		if (!s[m])
		{
			while (m--)
				free(s[m]);
			free(s);
			return (NULL);
		}
		custom_strncpy(s[m], str + l, p);
		s[m][p] = '\0';
		l += p;
	}
	s[m] = NULL;
	return (s);
}
/**
*_strwd2 - splits a string into array of words
*@str: - string to split
*@del: - delimeter param
*Return: - returns pointerto array of words or null
*/
char **_strwd2(char *str, char del)
{
	int m, n, o = 0, p = 0;
	char **s;

	if (!str || !*str)
		return (NULL);
	for (m = 0; str[m]; m++)
		if (str[m] != del && (str[m + 1] == del ||
			!str[m + 1]))
			p++;
	if (!p)
		return (NULL);
	s = malloc((p + 1) * sizeof(char *));
	if (!s)
		return (NULL);
	for (m = 0, n = 0; n < p; n++)
	{
		while (str[m] == del)
			m++;
		while (str[m + o] != del && str[m + o])
			o++;
		s[n] = malloc((o + 1) * sizeof(char));
		if (!s[n])
		{
			while (n--)
				free(s[n]);
			free(s);
			return (NULL);
		}
		custom_strncpy(s[n], str + m, o);
		s[n][o] = '\0';
		m += o;
	}
	s[n] = NULL;
	return (s);
}
