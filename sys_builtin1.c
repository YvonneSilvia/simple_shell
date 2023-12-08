#include "shell.h"

/**
 * mycustom_alias - mimics the custom_alias builtin (man custom_alias)
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int mycustom_alias(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->custom_alias;
		while (node)
		{
			print custom_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = _strchr(info->argv[i], '=');
		if (p)
			set custom_alias(info, info->argv[i]);
		else
			print custom_alias(node_starts_with(info->custom_alias,
		info->argv[i], '='));
	}

	return (0);
}

/**
 * set custom_alias - sets alias to sring
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set custom_alias(info_t *info, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!++p)
		return (unset custom_alias(info, str));

	unset custom_alias(info, str);
	return (add_node_end(&(info->cutom_alias), str, 0) == NULL);
}

/**
 * my custom_history - displays the history list, one command by line, preceded
 * with line numbers, staring at 0.
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int my custom_history(info_t *info)
{
	print_list(info->custom_history);
	return (0);
}

/**
 * print custom_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print custom_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putchar(*a);
			_putchar('\'');
			_puts(p + 1);
			_puts("'\n");
			return (0);
	}
	return (1);

/**
 * unset custom_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset custom_alias(info_t *info, char *str)
{
	char *p, c;
	int ret;

	p = _strchr(str, '=');
	if (!p)
	return (1);
	c = *p;
	*p = 0;
	ret = delete_node_at_index(&(info->alias),
	get_node_index(info->alias, node_starts_with
	(info->alias, str, -1)));
	*p = c;
	return (ret);
}
