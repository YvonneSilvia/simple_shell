#include "shell.h"
/**
 * _mysetenv - Initialize a new environment variable,
 * or modify an existing one
 * @info: Structure containg potential arguments. Used to maintain 
 * constant function prototype.
 * Return: Always 0
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{ 
		_eputs("Incorrect numberof arguements\n");
		return (1);
	} 
	if (_setenv(info, info->argv[1], info->argv[2]))
	       return (0);
	return (1);
}
/**
 * _myenv -prints the current environment
 * @info: Structure containing potential arguements. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}
/**
 * _myusetenv - Remove an environment variable
 * @info: Structure containg potential arguements. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int _myunsetenv(info_t *info)
{
	int j;

	if(info->argc == 1)
	{
		_eputs("Too few arguements.\n"):
		return (1);
	}
	for(j = 1; j <= info->argv ; j++)
		_unsetenv(info, info->argv[j]);
	return (0);
}
/**
 * _getenv - gets the value of an environ variable
 * @info: Structure containing potential arguments. Used to maintain
 * Return: the value
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = begin_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}
/**
 * populate_env_list - populate env linked list
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t j;

	for (j = 0; environ[j]; i++)
		add_node_at_end(&node, eviron[i], 0);
	info->env = node;
	return (0);
}
