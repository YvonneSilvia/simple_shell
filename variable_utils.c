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
	if (buffer[curr_pos] == '|' && buffer[curr_pos + 1] == '|')
	{
		buffer[curr_pos] = 0;
		curr_pos++;
		info->command_buffer_type = CMD_OR;
	}
	else if (buffer[curr_pos] == '&' && buffer[curr_pos + 1] == '&')
	{
		buffer[curr_pos] = 0;
		curr_pos++;
		info->command_buffer_type = CMD_AND;
	}
	else if (buffer[curr_pos] == ';')
	{
		buffer[curr_pos] = 0;
		info->command_buffer_type = CMD_CHAIN;
	}
	else
		return (0);
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
			_strdup(conver_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[i][1], '=');
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
		node = node_starts_with(info->alias, info->argv[0], '=');
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
void _check_chain(info_t *info, char buffer, size_t *curr, size_t start, size_t size)
{
	if (info->command_buffer_type == CMD_AND)
	{
		buffer[start] = info->status ? : buffer[start];
		*curr = info->status ? size : *curr;
	}
	if (info->command_buffer_type == CMD_OR)
	{
		buffer[start] = !info->status ? 0 : buffer[start];
		*curr = !info->status ? size : *curr;
	}
}
