/**
 * custom_unsetenv - Remove an environment variable
 * @info: Strucure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
int custom_unsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = begin_with(node->str, var);
		if (p && *p == '=')
		{
			info->env_changed = delete_node_at_someindex(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->env_changed);
}

/**
 * custom_get_environ - returns the string array copy of our environ
 * @info: Structure containing potential arguments. Used to maintain
 * Return: Always 0
 */
char **custom_get_environ(info_t *info)
{
	if (!info->environ || info->env_chnaged)
	{
		info->environ = list2string(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * custom_setenv - Initialize a new environment variable,
 * or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 * Return: Always 0
 */
int custom_setenv(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strncpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = info->env;
	while (node)
	{
		p = begin_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_at_end(&(info_env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}
