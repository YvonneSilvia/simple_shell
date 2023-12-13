#include "shell.h"
/**
*_is_chain - chaecks for chained commands
*@info: - struct type param
*@buffer: - buffer
*@curr_pos: - pointer to buffer current pos
*Return: - returns 1 success 0 otherwise
*/
int _is_chain(info_t *info, char *buffer, size_t *curr_pos)
{
	size_t p = *curr_pos;

	if (buffer[p] == '|' && buffer[p + 1] == '|')
	{
		buffer[p] = 0;
		p++;
		info->command_buffer_type = CMD_OR;
	}
	else if (buffer[p] == '&' && buffer[p + 1] == '&')
	{
		buffer[p] = 0;
		p++;
		info->command_buffer_type = CMD_AND;
	}
	else if (buffer[p] == ';')
	{
		buffer[p] = 0;
		info->command_buffer_type = CMD_CHAIN;
	}
	else
		return (0);
	*curr_pos = p;
	return (info->command_buffer_type ? 1 : 0);
}
/**
*replace_variables - replaces variables in a tokenized string
*@info: - struct type param
*Return: - returns 1 success 0 otherwise
*/
int replace_variables(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;
		if (!_strcmp(info->argv[i], "$?"))
		{
			replace_string(&(info->argv[i]),
				_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[i], "$$"))
		{
			replace_string(&(info->argv[i]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_begin_with(info->env, &info->argv[i][1], '=');
		if (node)
		{
			replace_string(&(info->argv[i]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[i], _strdup(""));
	}
	return (0);
}
/**
*_replace_alias - replaces an alias
*@info: - struct type param
*Return: - returns 1 success 0 otherwise
*/
int _replace_alias(info_t *info)
{
	char *p;
	list_t *node;

	while (1)
	{
		node = node_begin_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}
/**
*_check_chain - checks if we should continue to chain
*@info: - struct type param
*@buffer: - buffer
*@curr: - current postion
*@start: - starting position
*@size: - size of the buffer
*Return: - returns nothing
*/
void _check_chain(info_t *info, char *buffer, size_t *curr, size_t start, size_t size)
{
	if (info->command_buffer_type == CMD_AND)
	{
		buffer[start] = info->status ? buffer[start] : 0;
		*curr = info->status ? size : *curr;
	}
	if (info->command_buffer_type == CMD_OR)
	{
		buffer[start] = !info->status ? buffer[start] : 0;
		*curr = !info->status ? size : *curr;
	}
}
/**
*replace_string - replaces a string
*@new: - new string
*@old: - old string
*Return: - returns 1 success 0 otherwise
*/
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
